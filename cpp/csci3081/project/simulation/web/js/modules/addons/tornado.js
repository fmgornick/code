import * as THREE from '../../three.module.js';

class Tornado {
    constructor(scene) {
        this.scene = scene;
        this.obj = undefined;
    }

    init() {
        var tMAt = new THREE.PointsMaterial({
            color: 'rgba(80, 80, 80, 0.2)',
            transparent: true,
            opacity: 0.65,
            size: 0.75
          });
          
          let tornado = [];
          var t = 0;
          for (let i = 0; i < 70; i++) {
            t = 100 * i;
            let droplets = new THREE.Geometry();
          
            for (var p = 0; p < t; p++) {
              var pX = Math.random() * 0.2 * (i * 0.1 * i) - 0.15 * (i * 0.075 * i) + (Math.random() * 5 - 2.5),
                pY = (Math.random() + 1) * i * 0.5,
                pZ = Math.random() * 0.2 * (i * 0.1 * i) - 0.15 * (i * 0.075 * i) + (Math.random() * 5 - 2.5);
                let v = new THREE.Vector3(pX, pY, pZ);
          
              droplets.vertices.push(v);
            }
            tornado[i] = new THREE.Points(droplets, tMAt);
          
        }
        this.obj = tornado;
        this.scene.add(this.obj);
    }

    update() {
        let tct = 0;
        this.obj.forEach(t => {
            if (tct % 2 == 0) {
                t.rotation.y += (0.15 * (1 - tct / 70));
            } else {
                t.rotation.y -= (0.15 * (1 - tct / 70));
            }
            t.x += 0.1;
            t.geometry.verticesNeedUpdate = true;
            tct++;
        });
    }

    clear() { this.scene.remove(this.obj); this.obj = undefined; }

} export { Tornado };