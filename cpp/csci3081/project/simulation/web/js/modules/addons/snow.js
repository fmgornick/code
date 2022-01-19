import * as THREE from '../../three.module.js';

class Snow {
    constructor(scene) {
        this.scene = scene;
        this.obj = undefined;
    }

    init() {
        let snow;
        let particleCount = 1000,
        particles = new THREE.Geometry(),
        pMaterial = new THREE.PointsMaterial({
            color: 'rgb(255,255,255)',
            size: 0.2
        });
      
        for (var p = 0; p < particleCount; p++) {
            var pX = Math.random() * 500 - 250,
                pY = Math.random() * 500 - 250,
                pZ = Math.random() * 500 - 250,
                particle = new THREE.Vector3(pX, pY, pZ);
        
            particles.vertices.push(particle);
            snow = new THREE.Points(
            particles,
            pMaterial);
        }
        this.obj = snow;
        this.scene.add(this.obj);
    }

    update() {
        this.obj.geometry.vertices.forEach(particle => {
            //BLIZZARD
            particle.y -= 0.6;
            particle.x += .6;
            if (particle.y < 0) {
                particle.x = Math.random() * 500 + -250;
                particle.y = Math.random() * 500 + -250;
                particle.z = Math.random() * 500 + -250;
            }
    //LIGHT SNOW
      // particle.y -= 0.05;
      // particle.x += Math.random() * .05 + -0.025;
      // particle.x += Math.random() * .05 + -0.025;
      // if (particle.y >40) {
      //   particle.y = -10
      //   }
        });
        this.obj.geometry.verticesNeedUpdate = true;
    }

    clear() { this.scene.remove(this.obj); this.obj = undefined; }

} export { Snow };