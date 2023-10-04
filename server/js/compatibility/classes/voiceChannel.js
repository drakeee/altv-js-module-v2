/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/server/index.d.ts" />
// import * as alt from "@altv/server";

requireBinding("shared/entity.js");

class VoiceChannel extends alt.VoiceChannel {
    constructor(...args) {
        // NOTE (xLuxy): This prevents the infinite loop caused by alt.*.create
        if (!args.length) return super();

        const [spatial, maxDistance] = args;
        return alt.VoiceChannel.create({ spatial, maxDistance });
    }

    isPlayerInChannel(player) {
        return super.hasPlayer(player);
    }
}

alt.Factory.setVoiceChannelFactory(VoiceChannel);
cppBindings.registerCompatibilityExport("VoiceChannel", VoiceChannel);