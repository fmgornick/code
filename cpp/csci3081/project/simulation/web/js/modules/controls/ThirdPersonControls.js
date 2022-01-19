import * as THREE from '../../three.module.js';

class ThirdPersonControls {
    constructor(camera, container) {
        this._container = container;
        this._camera = camera;
        this._time = 0;
        this._theta = 2;
        this._phi = 2;
        this._turnSpeed = 1;
        this._speed = 2;
        this._radius = 50;
        this._focus = new THREE.Vector3(0, 0, 0);
        this._posMove = [0, 0, 0];
        this._negMove = [0, 0, 0];
        this._posTurn = [0, 0];
        this._negTurn = [0, 0];
        this._dynamic = false;
        this._drag = false;
    }

    // get target() { return this._focus; }
    get turnSpeed() { return this._turnSpeed; }
    get speed() { return this._speed; }
    get dynamic() { return this._dynamic; }
    get drag() { return this._drag; }

    target(val) { this._focus = val; }
    set turnSpeed(val) { this._turnSpeed = val; }
    set speed(val) { this._speed = val; }
    set dynamic(val) { this._dynamic = val; }
    set drag(val) { this._drag = val; }

    move(axis, val) {
        (val > 0) ? this._posMove[axis] = val : this._negMove[axis] = val;
    }

    clearMove(axis, val) {
        (val > 0) ? this._posMove[axis] = 0 : this._negMove[axis] = 0;
    }

    turn(axis, val) {
        (val > 0) ? this._posTurn[axis] = val : this._negTurn[axis] = val;
    }

    clearTurn(axis, val) {
        (val > 0) ? this._posTurn[axis] = 0 : this._negTurn[axis] = 0;
    }

    update(dt = 0) {
        this._theta += this._turnSpeed * (this._posTurn[0] + this._negTurn[0]) * dt;
        this._phi += this._turnSpeed * (this._posTurn[1] + this._negTurn[1]) * dt;
        let maxAng = 89 * Math.PI / 180;
        this._phi = Math.min( maxAng, Math.max( 0.1 , this._phi ));
        let depthX = (1 - Math.cos(this._theta) * this._radius);

        let sinPhi = Math.sin(this._phi);
        let cosPhi = Math.cos(this._phi);
        let cosTheta = Math.cos(this._theta);
        let sinTheta = Math.sin(this._theta);

        let camPos = new THREE.Vector3(this._focus.position.x + sinTheta*sinPhi*this._radius, this._focus.position.y + cosPhi*this._radius, this._focus.position.z - sinPhi*cosTheta*this._radius);
        let forwardDir = new THREE.Vector3(sinTheta *this._radius, sinPhi *this._radius,  depthX).normalize();
        let upDir = new THREE.Vector3(0, 1, 0);
        let rightDir = new THREE.Vector3(forwardDir.x, forwardDir.y, forwardDir.z);
        rightDir.cross(upDir).negate();

        let x = this._focus.position.x;
        let y = this._focus.position.y;
        let z = this._focus.position.z;

        if (this._dynamic) {

            x += this._speed[0] * (this._posMove[0] + this._negMove[0]) * this._rightDir.x;
            y += this._speed[0] * (this._posMove[0] + this._negMove[0]) * this._rightDir.y;
            z += this._speed[0] * (this._posMove[0] + this._negMove[0]) * this._rightDir.z;
            
            x += this._speed[1] * (this._posMove[1] + this._negMove[1]) * this._upDir.x;
            y += this._speed[1] * (this._posMove[1] + this._negMove[1]) * this._upDir.y;
            z += this._speed[1] * (this._posMove[1] + this._negMove[1]) * this._upDir.z;

            x += this._speed[2] * (this._posMove[2] + this._negMove[2]) * this._forwardDir.x;
            y += this._speed[2] * (this._posMove[2] + this._negMove[2]) * 0;
            z += this._speed[2] * (this._posMove[2] + this._negMove[2]) * this._forwardDir.z;

        }

        this._focus.rotation.y = -this._theta;

        this._focus.position.set(x, y, z);
        this._camera.position.set(camPos.x, camPos.y, camPos.z);
        this._camera.lookAt(this._focus.position);
    }

} export { ThirdPersonControls }