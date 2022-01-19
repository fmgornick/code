import * as THREE from '../../three.module.js';
import { GLTFLoader } from './GLTFLoader.js';
import { OBJLoader } from './OBJLoader.js';
import { MTLLoader } from './MTLLoader.js';

const glbLoader = new GLTFLoader();
const objLoader = new OBJLoader();

let dir = "../assets/models/";

export function setDir(d) {
    dir = d;
}

export function load(scene, models, mixers, params, dynamic = true) {
    let arr = params.path.split('.');
    let ext = arr[arr.length - 1];
    switch (ext) {
        case "glb":
            loadGlb(scene, models, mixers, params, dynamic);
            break;
        case "obj":
            loadObj(scene, models, params, dynamic, params.mtl);
            break;
        default:
            console.log("invalid model type in Loader");
            break;
    }
}

export async function loadAsync(params, dynamic = true) {
    let data = await glbLoader.loadAsync(`${dir}${params.path}`);
    return format(data, params, dynamic);
}

function format(obj, params, dynamic) {
    let model = obj.scene;

    model.position.copy(new THREE.Vector3(params.position[0], params.position[1], params.position[2]))

    model.scale.copy(new THREE.Vector3(params.scale[0], params.scale[1], params.scale[2])) //*1.41

    let mixer = null;

    let mixers = [];

    const animation = obj.animations[0];
    if (!(typeof animation === "undefined")) {
        mixer = new THREE.AnimationMixer(model);
        mixer.clipAction( animation ).play();
        mixers.push( {mixer: mixer, start: params.start, duration: params.duration} );
    }

    let o = {
        name: params.name,
        model: model,
        mixer: mixers,
        type: params.type,
        dynamic: dynamic,
        id: params.entityId,
        camera: new THREE.PerspectiveCamera( 55, window.innerWidth / window.innerHeight, 1, 1000 )
    }

    return o;
}

function loadObj(scene, models, params, dynamic, mtl) {
    let mtlLoader = new MTLLoader();
    mtlLoader.load( `../assets/model/${mtl}`, function( materials ) {
    
        materials.preload();
    
        objLoader.setMaterials( materials );
        objLoader.load( `../assets/model/${params}`, function ( object ) {
    
            if (dynamic) {
                models.push(object);
            }
    
            scene.add(object.scene);
    
        }, onProgress, onError );
    
    });
}

let onProgress = function(xhr) {
    if ( xhr.lengthComputable ) {
        const percentComplete = xhr.loaded / xhr.total * 100;
        console.log( Math.round( percentComplete, 2 ) + '% downloaded' );
        if (percentComplete == 100) {
        console.log("Model loaded");
        }
    }
};

let onError = function() { console.log("failed to load model"); };

export function umn(scene, completed) {
    let sceneModel = "../assets/model/umn.obj";
    let sceneTexture = "../assets/texture/umn.png";
  
    // load a resource
    objLoader.load(
      // resource URL
      sceneModel,
      // called when resource is loaded
      function (object) {
        object.position.copy(new THREE.Vector3(0, -13, 0))
        object.scale.copy(new THREE.Vector3(0.05, 0.05, 0.05));
  
        const textureLoader = new THREE.TextureLoader();
        const texture = textureLoader.load(sceneTexture + "-ground.png");
        texture.encoding = THREE.sRGBEncoding;
        texture.anisotropy = 16;
        var objmaterial = new THREE.MeshStandardMaterial({ map: texture });
  
        const texture2 = textureLoader.load(sceneTexture);
        texture.encoding = THREE.sRGBEncoding;
        texture.anisotropy = 16;
  
        object.traverse(function (node) {
          if (node.name == "EXPORT_GOOGLE_SAT_WM") {
            node.material = objmaterial;
            //node.material = new THREE.MeshDepthMaterial();
          }
          else if (node.name == "Areas:building") {
            var material = new THREE.MeshStandardMaterial({ color: 0x85868f, map: texture2 });
            node.material = material;
            //node.material = new THREE.MeshDepthMaterial();
          }
          else if (!node.isGroup) {
            node.visible = false;
          }
          console.log(node);
  
        });
  
        // models.push(object);
        scene.add(object);
        completed();
      }, function(xhr) {
		console.log( ( xhr.loaded / xhr.total * 100 ) + '% loaded' );
	  }, onError);
  }
