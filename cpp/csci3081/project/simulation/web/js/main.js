// could add a local version to support no internet connection
import * as THREE from './three.module.js';
import { OrbitControls } from './modules/controls/OrbitControls.js';
import { load, umn } from './modules/loaders/loader.js';
import { Entity } from './modules/entity.js';
import * as Script from './modules/script.js';

// Web Sockets API for communication with the backend
let api = new WSApi();

let scene = new THREE.Scene();

const scaleFactor = 20;
//let origin = new THREE.Vector3(0, 264, 0);
let origin = new THREE.Vector3(0, 0, 0);
let bounds = {
  "x": [-1450, 1500],
  "y": [264, 264],
  "z": [-900, 900]
};


let controls;
var container = document.querySelector('#scene-container');
var cameraContainer = document.querySelector('#camera-container');
var container2 = document.querySelector('#camera-view-container');
const clock = new THREE.Clock();
let simSpeed = 1.0;
let target = "umn";
let renderer, colorRenderer, depthRenderer, renderer3;

let updateReady = false;
let mouseX, mouseY;
let objMaterial;
let scriptsDir = "./scenes/";
let modelsDir = "../assets/model/"
let renderGraph = false;

let camera;
let actorCamera;
let miniMapShow = false;
let currentView = -1;
let entities = [];
let otherEntities = [];
let firstPerson = false;

let cam1, cam2;

class Scene {
  constructor(name, background) {
    this.name = name;
    this.background = background;
  }
  background() {
    return this.background;
  }
}

function coordTransform(a, scale = 20) {
  let b = new THREE.Vector3(a.x, a.y, a.z);
  b.x = 1.4*b.x / (scale);
  b.y = 0;
  b.z = 1.4*b.z / (scale);
  return b;
}

$.fn.buildBatteryDisplay = () => {
  let wrap = document.getElementById("battery-wrapper");
  let barEmpty = document.createElement("div");
  barEmpty.className = "battery-bar-empty";
  let bar = document.createElement("div");
  bar.id = "battery-bar-fill";
  bar.style.width = "1%";
  barEmpty.append(bar);
  wrap.append(barEmpty);
}

$("a[data-role='generate']").click(function () {
  let target = $(this).attr('id');
  console.log("attempting to generate " + target);
  Script.generate(target).then(function (data) {
    let e = new Entity(data[0]);
    console.log(e);
    entities.push(e);
    scene.add(e.model);
    api.sendCommand("createEntity", data[1]);
  });
});

$("span#route-toggle").click(function () {
  renderGraph = !renderGraph;
  if (renderGraph) {
    scene.add(group);
  } else {
    scene.remove(group);
  }
});

api.onmessage = function (msg, data) {
  // interprets data from backend sent through observer
  if ("notification" in data) {
    $.fn.display(data);
  }
  if ("takePicture" in data) {
    sendImage(data["takePicture"]);
  }
}

// creates a scene class
// paramaters are: name, background color/image, preloaded model references
let umnScene = new Scene(target, new THREE.Color('skyblue'));

// scene object to hold multiple scene information
let scenes = { target: umnScene };

// saves the image to a base64 encoded jpg file
var strDownloadMime = "image/octet-stream";
function saveImage() {
  sendImage(-1);
}

function sendImage(cameraId) {
  var imgData;
  var depthData;
  try {
      let cam = camera;
      if (currentView >= 0 && firstPerson) {
        cam = actorCamera;
      }
      if (cameraId >= 0) {
        cam = entities[cameraId].camera;
      }
      scene.overrideMaterial = objMaterial;
      depthRenderer.render( scene, cam );
      scene.overrideMaterial = null;
      colorRenderer.render( scene, cam );
      scene.overrideMaterial = null;
      var strMime = "image/jpeg";
      imgData = colorRenderer.domElement.toDataURL(strMime,.8);
      depthData = depthRenderer.domElement.toDataURL(strMime,.8);
      api.sendPostCommand("image", {position: [cam.position.x, cam.position.y, cam.position.z], images: [imgData, depthData], cameraId: cameraId}).then(function(data) {});
  } catch (e) {
      console.log(e);
      return;
  }
}

//========================================SCENE GENERATION==========================================
// This function runs the scene
let group = new THREE.Group();
function start() {

  const gridMaterial = new THREE.LineBasicMaterial({ color: 0x0000ff });
  let maxVec = new THREE.Vector3(-9999999, -9999999, -9999999);
  let minVec = new THREE.Vector3(9999999, 9999999, 9999999);
  console.log('building graph');
  $.getJSON("./scenes/graph.json", function (data) {
    for (var i = 0; i < data.length; i++) {
      const points = [];
      let node = data[i].node;
      // console.log("****************************************************");
      // console.log(node.id);
      // console.log(node.position);
      let converted = coordTransform(node.position);
      // console.log("converted is: ");
      // console.log(converted);
      points.push(converted);
      if (-node.position.x < minVec.x) {
        minVec.x = node.position.x;
      }
      if (node.position.y < minVec.y) {
        minVec.y = node.position.y;
      }
      if (-node.position.z < minVec.z) {
        minVec.z = node.position.x;
      }
      if (-node.position.x > maxVec.x) {
        maxVec.x = node.position.x;
      }
      if (node.position.y > maxVec.y) {
        maxVec.y = node.position.y;
      }
      if (-node.position.z > maxVec.z) {
        maxVec.z = node.position.z;
      }
      // console.log(Object.keys(node.edges).length);
      for (let e in node.edges) {
        let line = points;
        let edge = node.edges[e].position;
        // console.log(edge);
        let convertedEdge = coordTransform(edge);
        line.push(convertedEdge);
        const geometry = new THREE.BufferGeometry().setFromPoints(line);
        const draw = new THREE.Line(geometry, gridMaterial);
        group.add(draw);
        line = [];
      }
    }
  }).then(function (data) {
    // console.log("======MAP DIMENSIONS ARE=======");
    // console.log(maxVec);
    // console.log(minVec); 
    let midX = (maxVec.x + minVec.x) / 2;
    let midZ = (maxVec.z + minVec.z) / 2;
    if (renderGraph) {
      scene.add(group);
    }
    // console.log("mid x is: "+midX);
    // console.log("mid z is: "+midZ);
    // origin.set(midX, 264, midZ);
  });

  var simSpeedSlider = document.getElementById("simSpeed");

  // Update the current slider value (each time you drag the slider handle)
  simSpeedSlider.oninput = function () {
    simSpeed = this.value / 10.0;
  }

  $("#firstPerson").attr("disabled", true);

  $('#entitySelect').on("change", function () {
    $("#firstPerson").removeAttr("disabled");
    currentView = $("#entitySelect").val();
    if (currentView >= 0) {
      controls.target.copy(entities[currentView].model.position);
      controls.update();
    }
    else {
      firstPerson = false;
      $("#firstPerson").prop("checked", false);
      $("#firstPerson").attr("disabled", true);
    }
    $("#entitySelect").blur();
  });

  $('#firstPerson').on("change", function () {
    firstPerson = !firstPerson;
  });

  // initializes scene and camera
  camera = new THREE.PerspectiveCamera(55, window.innerWidth / window.innerHeight, 1, 1000);
  camera.position.set(origin.x - 10, origin.y + 10, origin.z + 10);//30, 30, 100 );
  scene = new THREE.Scene();

  actorCamera = new THREE.PerspectiveCamera(55, window.innerWidth / window.innerHeight, 1, 1000);

  // depth shader material override code
  var uniforms = {
    time: { type: "f", value: 1.0 },
    resolution: { type: "v2", value: new THREE.Vector2() },
    viewMatrixInverse: { type: 'm4', value: new THREE.Matrix4() }
  };

  uniforms.resolution.value.x = window.innerWidth;
  uniforms.resolution.value.y = window.innerHeight;
  uniforms.time.value = 1.0;

  objMaterial = new THREE.ShaderMaterial({
    uniforms: uniforms,
    vertexShader: document.getElementById('vertexShader').textContent,
    fragmentShader: document.getElementById('fragmentShader').textContent
  });

  // skybox generation and dynamic backgrounds for multiple scenes
  if (target != undefined) {
    let bg = scenes.target.background;
    if (typeof bg === "string") {

      // uses a skybox (sphere) by rendering a texture on the inside of sphere
      const geometry = new THREE.SphereGeometry(1000, 60, 40);
      geometry.scale(- 1, 1, 1);

      const texture = new THREE.TextureLoader().load(`../assets/texture/hdr/${bg}`);
      const material = new THREE.MeshBasicMaterial({ map: texture });

      const mesh = new THREE.Mesh(geometry, material);
      scene.add(mesh);

    } else {
      scene.background = scenes.target.background;
    }
  } else {
    console.log(scenes);
    console.log(scenes.retro.background);
    scene.background = scenes.retro.background;
  }

  // adds lighting to the scene
  const ambientLight = new THREE.AmbientLight(0xffffff, 1.0);
  scene.add(ambientLight);
  const light = new THREE.DirectionalLight(0xffffff, 1.0);
  light.position.set(10, 10, 10);
  scene.add(ambientLight, light);
  const light2 = new THREE.DirectionalLight(0xffffff, 1.0);
  light2.position.set(0, 10, -10);
  scene.add(ambientLight, light2);

  // screenshot link generation
  var saveLink = document.createElement('div');
  saveLink.style.position = 'absolute';
  saveLink.style.top = '60px';
  saveLink.style.width = '100%';
  saveLink.style.color = 'white !important';
  saveLink.style.textAlign = 'center';
  saveLink.innerHTML = '<a href="#" id="saveLink">Take Picture</a>';
  document.body.appendChild(saveLink);
  document.getElementById("saveLink").addEventListener('click', saveImage);

  //====================================SCENE RENDERER==============================================

  // prevents multiple canvases from being generated on scene change
  $('canvas:nth-of-type(1)').remove();

  // standard renderer
  renderer = new THREE.WebGLRenderer({ container, alpha: true, antialias: true, preserveDrawingBuffer: true });
  renderer.setSize(window.innerWidth, window.innerHeight);
  container.appendChild(renderer.domElement);

  // depth renderer for taking images
  colorRenderer = new THREE.WebGLRenderer({ cameraContainer, alpha: true, antialias: true, preserveDrawingBuffer: true });
  colorRenderer.setPixelRatio(window.devicePixelRatio);
  colorRenderer.setSize(window.innerWidth / 2.0, window.innerHeight / 2.0);
  document.body.appendChild(colorRenderer.domElement);

  // depth renderer for taking images
  depthRenderer = new THREE.WebGLRenderer({ cameraContainer, alpha: true, antialias: true, preserveDrawingBuffer: true });
  depthRenderer.setPixelRatio(window.devicePixelRatio);
  depthRenderer.setSize(window.innerWidth / 2.0, window.innerHeight / 2.0);
  document.body.appendChild(depthRenderer.domElement);

  // copies depth renderer to mini display
  renderer3 = new THREE.WebGLRenderer({ container2, alpha: true, antialias: true, preserveDrawingBuffer: true });
  renderer3.setPixelRatio(window.devicePixelRatio);
  renderer3.setSize(window.innerWidth / 4, window.innerHeight / 4);
  container2.appendChild(renderer3.domElement);

  // adds extra aesthetic code (may refactor to modules)
  // controls and other shaders. (Ocean and weather patterns were removed)
  // define controls
  controls = new OrbitControls(camera, container);
  controls.maxPolarAngle = Math.PI * 0.695;
  controls.target.copy(origin);
  controls.update();

  cam1 = camera;

  // start the animation/render loop
  renderer.setAnimationLoop(() => {
    update();
    render();
  });
}

async function build() {
  let arr = target.split("-");
  if (arr[1] == "ec") {
    $.fn.buildBatteryDisplay();
  }
  if (arr[0] == "umn") {
    umn(scene, true);
    Script.run(`${scriptsDir}${target}.json`, modelsDir, api).then(function (data) {
      Promise.all(data).then(function (_entities) {
        console.log("###########################");
        for (let e of _entities) {
          let d = new Entity(e);
          console.log(d);
          entities.push(d);
          scene.add(d.model);
        }

        Script.generate("other").then(function (data) {
          let e = new Entity(data[0]);
          console.log(e);
          entities.push(e);
          scene.add(e.model);
          otherEntities.push(data[1]);
        });
        updateReady = true;
      });
    });
  }
}

async function main() {
  start();
  await build();
}
// this runs everything
main();

// takes an image every 5 seconds
// window.setInterval( sendImage, 5000);

// This is the function that is called once the document is started.
$(document).ready(function () {

  // Start checking for when the user resizes their application window.
  window.addEventListener('resize', onWindowResize);

  // interprets key press or release and sends information to backend
  var keyAction = function (e) {
    if (!e.repeat) {
      api.sendCommand(e.type, { key: e.key, keyCode: e.keyCode });
      console.log(e);
    }
  }

  document.onkeydown = keyAction;
  document.onkeyup = keyAction;

  $("#camera-trigger").on('click', function () {
    miniMapShow = !miniMapShow;
  });

});

// This function updates the scene's animation cycle.
var time = 0.0;

function update() {
  // Get the time since the last animation frame.
  const delta = clock.getDelta();
  time += delta;

  if (!miniMapShow) {
    container2.style.display = "none";
  } else {
    container2.style.display = "block";
  }

  for (const e of entities) {
    if (e.type == "actor" && otherEntities.length > 0) {
      //console.log(e, otherEntities.length);

      for (const a of otherEntities) {
        let dist = 0.0;
        dist += Math.pow(e.model.position.x - a.position[0], 2.0);
        dist += Math.pow(e.model.position.y - a.position[1], 2.0);
        dist += Math.pow(e.model.position.z - a.position[2], 2.0);
        dist = Math.sqrt(dist);
        if (dist < 5.0) {
          api.sendCommand("createEntity", a);
          otherEntities = [];
        }
      }
    }

    for (const mixer of e.mixer) {
      if (mixer.start == undefined || mixer.duration == undefined) {
        mixer.mixer.update(delta);
      }
      else {
        var newTime = time - mixer.start;
        var iterations = Math.floor(newTime / mixer.duration);
        newTime = newTime - iterations * mixer.duration + mixer.start;
        mixer.mixer.setTime(newTime);
      }
    }
  }

  controls.update();

  if (updateReady) {

    api.sendCommand("update", { delta: delta, simSpeed: simSpeed }).then(function (updateData) {
      let data = updateData;
	    for (let e in data) {
	      if (e !== "id") {
	        let idx = data[e].entityId;
	        entities[idx].model.position.copy(new THREE.Vector3(data[e].pos[0], data[e].pos[1], data[e].pos[2]));
	        var dir = new THREE.Vector3(data[e].dir[0], data[e].dir[1], data[e].dir[2]);
	        var adjustedDirVector = dir;
	        adjustedDirVector.add(entities[idx].model.position);
	        entities[idx].model.lookAt(adjustedDirVector);

	        let cam =  entities[idx].camera;
	        cam.position.copy(entities[idx].model.position);
	        cam.lookAt(adjustedDirVector);

	        if (currentView == idx) {
	          actorCamera =  cam;
	          controls.target.copy(entities[idx].model.position);
	          controls.update();
	        }

	      }
      }
      updateReady = true;
      render();
    });
    //updateReady = false;
  }
}

// ===================================MULTIPLE RENDERERS============================================

let miniMap = {
  left: 0.6,
  bottom: 0.05,
  width: 0.3,
  height: 0.4
};

// renders all renderers to support depth images
function render() {
  if (firstPerson && currentView >= 0) {
    renderer.render(scene, actorCamera);
  }
  else {
    renderer.render(scene, camera);
  }

  if (miniMapShow) {
    const left = Math.floor(container2.clientWidth * miniMap.left);
    const bottom = Math.floor(container2.clientHeight * miniMap.bottom);
    const width = Math.floor(container2.clientWidth * miniMap.width);
    const height = Math.floor(container2.clientHeight * miniMap.height);

    // allows minimap through split render
    renderer3.setViewport(left, bottom, width, height);
    renderer3.setScissor(left, bottom, width, height);
    renderer3.setScissorTest(true);
    renderer3.render(scene, actorCamera);
  }



}

// This function updates the projection matrix and renderer whenever the
// user's application window is resized.
function onWindowResize() {

  // set the aspect ratio to match the new browser window aspect ratio
  camera.aspect = container.clientWidth / container.clientHeight;

  // update the camera's frustum
  camera.updateProjectionMatrix();

  // update the size of the renderer AND the canvas
  // need to add resize support for minimap
  renderer.setSize(container.clientWidth, container.clientHeight);
  // colorRenderer.setSize( );

}

// returns mouse data in device pixels (not out of -1 and 1)
function onMouseMove(event) {
  mouseX = (event.clientX - window.innerWidth / 2);
  mouseY = (event.clientY - window.innerHeight / 2);
}

// this functions allows depth camera and normal scene to swap on minimap click
window.addEventListener('click', function (e) {
  let x = mouseX / this.window.innerWidth;
  let y = mouseY / this.window.innerHeight;
  if (x <= -0.25 && y <= -0.25) {
    let tempC = cam1;
    cam1 = actorCamera;
    actorCamera = tempC;
    controls.target.set(0, 0, 0);
  }
  console.log(`MouseX is ${x}`);
  console.log(`MouseY is ${y}`);
});

window.addEventListener('mousemove', onMouseMove, false);