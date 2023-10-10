/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";

requireBinding("shared/logging.js");

export class Entity extends alt.Entity {
    static getByScriptID(...args) {
        // NOTE (xLuxy): This method in v1 only returns WorldObject
        if (typeof super.getByScriptID == "function") {
            return super.getByScriptID(...args);
        }

        return null;
    }

    get isSpawned() {
        if (![alt.Enums.BaseObjectType.PLAYER, alt.Enums.BaseObjectType.LOCAL_PLAYER].includes(super.type)) {
            return super.isSpawned;
        }

        return super.scriptID != 0;
    }
}

cppBindings.registerCompatibilityExport("Entity", alt.Entity);