// main index.js

import { NativeModules } from 'react-native';

const { MediasoupClient } = NativeModules;

/*const EventEmitter = require("EventEmitter");
const BatchedBridge = require("BatchedBridge");

BatchedBridge.registerLazyCallableModule("MathEmitter", () => {
  return new EventEmitter();
});*/

export default MediasoupClient;
