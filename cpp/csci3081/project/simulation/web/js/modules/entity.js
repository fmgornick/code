class Entity {
    constructor(params) {
        if (params) {
            (params.name) ? this._name = params.name : this._name = "undefined";
            (params.id > -1) ? this._id = params.id : this._id = -1;
            (params.path) ? this._path = params.path : this._path = "undefined";
            (params.type) ? this._type = params.type : this._type = "undefined";
            (params.position) ? this._position = params.position : this._position = [0, 0, 0];
            (params.scale) ? this._scale = params.scale : this._scale = [1, 1, 1];
            (params.rotation) ? this._rotation = params.rotation : this._rotation = [0, 0, 0];
            (params.model) ? this._model = params.model : this._model = "undefined";
            (params.mixer) ? this._mixer = params.mixer : this._mixer = [];
            (params.dynamic) ? this._dynamic = params.dynamic : this._dynamic = false;
            (params.camera) ? this._camera = params.camera : this._camera = null;
        } else {
            console.log("not asynchronously loading");
        }
    }

    get name() { return this._name; }
    get id() { return this._id; }
    get path() { return this._path; }
    get position() { return this._position; }
    get scale() { return this._scale; }
    get rotation() { return this._rotation; }
    get model() { return this._model; }
    set name(val) { this._name = val; }
    get mixer() { return this._mixer; }
    get camera() { return this._camera; }
    get type() { return this._type; }

    addComponent(name) {
        this._components[name] = name;
    }

    update(dt) {
        if (this._dynamic) {

            if (this._name == "wumpa") {
                this._model.rotation.y += 2 * dt;
            }

        }
    }

} export { Entity }