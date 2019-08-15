import Vue from 'vue'
import Vuex from 'vuex'
import codegen from "./codegen"

Vue.use(Vuex)

const defaultFrames = {
	white: {
		duration: 250,
		frameNumber: 0,
		leds: [ 
			{id:"D1", color:"#00ffff", y:99, x:205, brightness:15},
			{id:"D2", color:"#00ffff", y:110, x:231, brightness:15},
			{id:"D3", color:"#ffff00", y:302, x:54, brightness:15},
			{id:"D4", color:"#ffff00", y:293, x:79, brightness:15},
			{id:"D5", color:"#ffff00", y:281, x:104, brightness:15},
			{id:"D6", color:"#00ff00", y:193, x:41, brightness:15},
			{id:"D7", color:"#00ff00", y:218, x:43, brightness:15},
			{id:"D8", color:"#00ff00", y:243, x:45, brightness:15},
			{id:"D9", color:"#00ff00", y:229, x:83, brightness:15},
			{id:"D10", color:"#ffff00", y:266, x:127, brightness:15}
		]
	},
	black: {
		duration: 250,
		frameNumber: 0,
		leds: [
			{id:"D1", color:"#ff0000", y:123, x:162, brightness:15, aliases: ["D2"]},
			{id:"D2", color:"#ff0000", y:114, x:187, brightness:15, aliases: ["D1"]},
			{id:"D3", color:"#ffff00", y:131, x:282, brightness:15, aliases: ["D4", "D5"]},
			{id:"D4", color:"#ffff00", y:93, x:294, brightness:15, aliases: ["D3", "D5"]},
			{id:"D5", color:"#ffff00", y:96, x:329, brightness:15, aliases: ["D3", "D4"]},
			{id:"D6", color:"#00ff00", y:235, x:224, brightness:15},
			{id:"D7", color:"#00ff00", y:233, x:259, brightness:15},
			{id:"D8", color:"#00ff00", y:241, x:292, brightness:15},
			{id:"D9", color:"#00ff00", y:248, x:323, brightness:15},
			{id:"D10", color:"#00ff00", y:261, x:351, brightness:15},
			{id:"D11", color:"#00ff00", y:284, x:213, brightness:15},
			{id:"D12", color:"#00ff00", y:297, x:250, brightness:15},
			{id:"D13", color:"#00ff00", y:312, x:291, brightness:15},
			{id:"D14", color:"#00ff00", y:314, x:338, brightness:15}
		]
	}
}

function ghettoCopy(obj) { return JSON.parse(JSON.stringify(obj)) }

export default new Vuex.Store({
	state: {
		currentSpyColor: "white",
		timeScalingFactor: 1,
		white: {
			animationId: 0,
			currentFrameNumber: 0,
			frames: [ ghettoCopy(defaultFrames.white) ]
		},
		black: {
			animationId: 0,
			currentFrameNumber: 0,
			frames: [ ghettoCopy(defaultFrames.black) ]
		},
	},
	getters: {
		animationId: function(state) {
			return state[state.currentSpyColor].animationId
		},
		timeScalingFactor: function(state) {
			return state.timeScalingFactor
		},
		currentFrameNumber: function(state, getters) {
			return state[getters.currentSpyColor].currentFrameNumber
		},
		currentSpyColor: function(state) {
			return state.currentSpyColor
		},
		frames: function(state, getters) {
			return state[getters.currentSpyColor].frames
		},
		currentFrame: function(state, getters) {
			return getters.frames[getters.currentFrameNumber]
		},
		frameCount: function(state, getters) {
			return getters.frames.length
		},
		frame: function(state, getters) {
			return function(frameNumber) {
				if (typeof frameNumber === "undefined") frameNumber = getters.currentFrameNumber
				return getters.frames[frameNumber]
			}
		},
		duration: function(state, getters) {
			return function(frameNumber) {
				if (typeof frameNumber === "undefined") frameNumber = getters.currentFrameNumber
				return getters.frames[frameNumber].duration
			}
		},
		leds: function(state, getters) {
			return function(frameNumber) {
				if (typeof frameNumber === "undefined") frameNumber = getters.currentFrameNumber
				return getters.currentFrame.leds
			}
		},
		findLed: function(state, getters) {
			var leds = getters.leds()
			return function(ledId) {
				for (var i in leds) {
					var led = leds[i]
					if (led.id === ledId) {
						return led
					}
				}
				return null
			}
		},
		frameShortCode: function(state, getters) {
			return function(frameNumber) {
				if (typeof frameNumber === "undefined") frameNumber = getters.currentFrameNumber
				return codegen.frameShortCode(getters.currentSpyColor, getters.animationId, frameNumber, getters.duration(frameNumber), getters.leds(frameNumber), true)
			}	
		},
		frameLongCode: function(state, getters) {
			return function(frameNumber) {
				if (typeof frameNumber === "undefined") frameNumber = getters.currentFrameNumber
				return codegen.frameLongCode(getters.currentSpyColor, getters.animationId, frameNumber, getters.duration(frameNumber), getters.leds(frameNumber), true)
			}
		},
		currentFrameLedLongCode: function(state, getters) {
			return function(ledId) {
				return codegen.ledLongCode(getters.currentSpyColor, getters.animationId, getters.currentFrameNumber, getters.findLed(ledId), getters.duration(), true)
			}
		},
		framesShortCode: function(state, getters) {
			return codegen.framesShortCode(getters.currentSpyColor, getters.animationId, getters.frames, true)
		}
	},
	mutations: {
		currentSpyColor: function(state, color) {
			state.currentSpyColor = color
			state[color].currentFrameNumber = state[color].currentFrameNumber
		},
		currentFrameNumber: function(state, n) {
			state[state.currentSpyColor].currentFrameNumber = n
		},
		addFrame: function(state, frame) {
			if (typeof frame === "undefined") {
				//frame = ghettoCopy(defaultFrames[state.currentSpyColor])
				var currentSpyColor = state.currentSpyColor
				var frames = state[currentSpyColor].frames
				var currentFrameNumber = state[currentSpyColor].currentFrameNumber
				var frame = ghettoCopy(frames[currentFrameNumber])
				frame.frameNumber = frames.length
			}
			state[state.currentSpyColor].frames.push(frame)
			state[state.currentSpyColor].currentFrameNumber = frame.frameNumber
		},
		removeFrame: function(state, frameNumber) {
			delete state[state.currentSpyColor].frames[frameNumber]
		},
		saveFrame: function(state, frame) {
			state[state.currentSpyColor].frames[frame.frameNumber] = frame
		},
		clearFrames: function(state) {
			state[state.currentSpyColor].currentFrameNumber = 0
			state[state.currentSpyColor].frames = [ ghettoCopy(defaultFrames[state.currentSpyColor]) ]
		},
		animationId: function(state, n) {
			state[state.currentSpyColor].animationId = n
		},
		timeScalingFactor: function(state, n) {
			state.timeScalingFactor = n
		}
	}
})
