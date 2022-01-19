import * as THREE from '../../three.module.js';

class Rain {
    constructor(scene) {
        this.scene = scene;
        this.obj = undefined;
    }

    init() {
        let rain;
        var dropletCount = 5000,
        droplets = new THREE.Geometry(),
        dropletMat = new THREE.PointsMaterial({
          color: 0x0FFFFF,
          size: 0.1
        });
      
        for (var p = 0; p < dropletCount; p++) {
            var pX = Math.random() * 500 - 250,
                pY = Math.random() * 500 - 250,
                pZ = Math.random() * 500 - 250,
                droplet = new THREE.Vector3(pX, pY, pZ);
      
            droplets.vertices.push(droplet);
            rain = new THREE.Points(
            droplets,
            dropletMat);
            this.obj = rain;
            this.scene.add(this.obj);
      }
    }

    update() {
        this.obj.geometry.vertices.forEach(p => {
            p.y -= 0.8;
            p.x -= 0.8;
            // p.x += Math.random() * .05 + -0.025;
            // p.x += Math.random() * .05 + -0.025;
            if (p.y < 0) {
                p.x = Math.random() * 500 + -250;
                p.y = Math.random() * 500 + -250;
                p.z = Math.random() * 500 + -250;
            }
        });
        // this.obj.geometry.verticesNeedUpdate = true;
    }

    clear() { this.scene.remove(this.obj); this.obj = undefined; }

} export { Rain };