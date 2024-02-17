/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";

/** @type {typeof import("../../../../shared/js/compatibility/utils/classes.js")} */
const { extendClassWithProperties } = requireBinding("shared/compatibility/utils/classes.js");

const { SharedBaseObject } = requireBinding("shared/compatibility/classes/sharedBaseObject.js");

extendClassWithProperties(alt.BaseObject, null, SharedBaseObject);

cppBindings.registerCompatibilityExport("BaseObject", alt.BaseObject);
