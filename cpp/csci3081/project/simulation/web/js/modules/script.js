import { WebGLRenderTarget } from '../three.module.js';
import { Entity } from './entity.js';
import * as Loader from './loaders/loader.js';
let _api;
let idx = -1;

export async function run(file, modelsDir, api) {
    _api = api;
    var _entities = [];
    Loader.setDir(modelsDir);
    let json = [];
    await $.getJSON(file, function(data) {
        json = data;
    });
    for (var i = 0; i < json.length; i++) {

        var command = json[i];

        if (command.command == "reset") {
            _api.sendCommand("reset", command.params);
        }

        if (command.command == "createEntity") {
            idx++;
            if (command.params.type == "actee") {
                command.params.position = [-90 + Math.random() * 180, 0, -50 + Math.random() * 100];       
            }
            let o = await Loader.loadAsync(command.params);
            _entities.push(o);

            $("#entitySelect").append($('<option value="' + command.params.entityId + '">' + command.params.name + '</option>'));
    
            _api.sendCommand("createEntity", command.params);
        }

        if (command.command == "terrain") {
            let o = await Loader.loadAsync(command.params, false);
            _entities.push(o);
    
            _api.sendCommand("createEntity", command.params);
        }

        if (command.command == "rescue") {
            _api.sendCommand("rescue", command.params);
        }
    }

    return _entities;
}

export async function generate(type) {
    idx++;
    let o = {
            "entityId": idx,
            "name": "undefined",
            "type": "undefined",
            "path": "undefined",
            "position": [0, 0, 0],     
            "scale": [1, 1, 1],
            "direction": [1,0,0],
            "radius": 1.0,
            "rotation": [0, 0, 0],
            "cameras": [idx]
    };
    switch(type) {
        case "drone":
            o.path = "drone.glb";
            o.type = "actor";
            o.name = `drone ${idx}`;
            o.scale = [0.15, 0.15, 0.15];
            o.position = [-90 + Math.random() * 180, 264, -50 + Math.random() * 100];
            break;
        case "other":
            o.path = "robot.glb";
            o.type = "actee";
            o.name = `robot`;
            o.position = [-90 + Math.random() * 180, 0, -50 + Math.random() * 100];       
            o.scale = [0.25, 0.25, 0.25];
            break;
        case "charger":
            o.path = "charger.glb";
            o.type = "charger";
            o.name = `recharge station ${idx}`;
            o.position = [-90 + Math.random() * 180, 0, -50 + Math.random() * 100];       
            break;
        default:
            break;
    }
    $("#entitySelect").append($('<option value="' + o.entityId + '">' + o.name + '</option>'));    
    let promise = await Loader.loadAsync(o);
    return [promise, o];
}
