/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";

requireBinding("shared/factory.js");

const { BaseObject } = requireBinding("client/compatibility/classes/baseObject.js");

const { extendAltEntityClass } = requireBinding("shared/compatibility/utils/classes.js");

class Audio extends alt.Audio {
    constructor(...args) {
        // NOTE (xLuxy): This prevents the infinite loop caused by alt.*.create
        if (!args.length) return super();

        const [source, volume, radio, clearCache] = args;

        const instance = alt.Audio.create({ source, volume, radio, clearCache });
        return extendAltEntityClass(instance, BaseObject);
    }

    static count() {
        return alt.Audio.all.length;
    }

    getEventListeners() {
        return super.listeners;
    }

    get playing() {
        return super.isPlaying;
    }

    getOutputs() {
        return super.outputs;
    }
}

alt.Factory.setAudioFactory(Audio);
cppBindings.registerCompatibilityExport("Audio", Audio);