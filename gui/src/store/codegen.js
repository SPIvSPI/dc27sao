function colorToIndex(color) {
	return color === "white" ? 0 : 1
}

function formatHex(val) {
	val = parseInt(val, 2)
	return `0x${zeroPad(val.toString(16), 4)}`
}

function zeroPad(val, width) {
	return ("0".repeat(width) + val).split("").reverse().slice(0,width).reverse().join("")
}

function formatBinary(val, includePrefix) {
   var str = includePrefix ? "0b" : ""
   str += `${zeroPad(val.toString(2), 4)}`
   return str
}

function packBinary() {
	var arr = [].slice.call(arguments)
	var str = ""
	arr.forEach(function(val) {
		val = 1*val
		str += formatBinary(val)
	})
	return str
}

function frameLongCode(spyColor, animationId, frameNumber, duration, leds, includeComments) {
	var code = ""
	if (includeComments) {
		var code = "// frames[i][j]\n// i : animationId\n// j : frameNumber\n"
	}
	leds.forEach(function(led) {
		code += ledLongCode(spyColor, animationId, frameNumber, led, false) + "\n"
	})	
	code += `frames[${animationId}][${frameNumber}].duration = 0x${duration.toString(16)};\n`
	return code
}

function ledLongCode(spyColor, animationId, frameNumber, led, includeComments) {
	var code = ""
	var n = led.id.slice(1)
	if (includeComments) {
		var code = "// frames[i][j]\n// i : animationId\n// j : frameNumber\n"
	}
	code += `frames[${animationId}][${frameNumber}].led${n} = 0x${led.brightness.toString(16)};`
	return code
}

function frameShortCode(spyColor, animationId, frameNumber, duration, leds, includeComments) {
	var bvals = []
	var code = ""
	if (includeComments) {
		//var code = "// frames[i][j]\n// i : animationId\n// j : frameNumber\n"
	}

	function find(id) {
		for (var i in leds) {
			var led = leds[i]
			if (led.id === id) {
				return led
			}
		}
		return null
	}
	
	function valueOf(id) {
		return find(id).brightness
	}

	var durHigh = [(duration & 0xf000) >> 12, (duration & 0x0f00) >> 8]
	var durLow = [(duration & 0x00f0) >> 4, (duration & 0x000f)]
	if (spyColor === "white") {
		bvals[0] = packBinary(valueOf("D4"), valueOf("D3"), valueOf("D2"), valueOf("D1"))
		bvals[1] = packBinary(valueOf("D8"), valueOf("D7"), valueOf("D6"), valueOf("D5"))
		bvals[2] = packBinary(0, 0, valueOf("D10"), valueOf("D9"))
		bvals[3] = packBinary(durHigh[0], durHigh[1], durLow[0], durLow[1])
	} else {
		bvals[0] = packBinary(valueOf("D7"), valueOf("D6"), valueOf("D3"), valueOf("D1"))
		bvals[1] = packBinary(valueOf("D11"), valueOf("D10"), valueOf("D9"), valueOf("D8"))
		bvals[2] = packBinary(0, valueOf("D14"), valueOf("D13"), valueOf("D12"))
		bvals[3] = packBinary(durHigh[0], durHigh[1], durLow[0], durLow[1])
	}

	code += '\t\t{ ';
	for (var i=0; i<bvals.length; i++) {
		//code += `frames[${animationId}][${frameNumber}].bytes[${i}] = ${formatHex(bvals[i])};\n`
		//code += `frames[${frameNumber}].bytes[${i}] = ${formatHex(bvals[i])};\n`
		code += `${formatHex(bvals[i])}`
		if (i < bvals.length-1) code += ', '
	}
	code += ' }';
	return code
}

function framesShortCode(spyColor, animationId, frames, includeComments) {
	var code = ""
	//code = `#if SPY == ${colorToIndex(spyColor)}\n\n`
	
	code += `#include "blinky_engine.h"\n`
	code += `#include "animations.h"\n\n`
	if (includeComments) {
		code += `// frameCount = ${frames.length}\n// animationId = ${animationId}\n\n`
	}
	code += `extern led_frame* animations[];\n`
	code += `extern uint16_t animations_framecounts[];\n`
	code += `${spyColor}_${animationId}() {\n`
	code += `\tcode led_frame aniframes[] = {\n`
	frames.forEach(function(frame, i) {
		code += frameShortCode(spyColor, animationId, frame.frameNumber, frame.duration, frame.leds, false)
		if (i < frames.length-1) code += ", "
		code += "\n"
	})
	code += `\t};\n` // aniframes
	code += `\tanimations_framecounts[${animationId}] = ${frames.length};\n`
	code += `\tanimations[${animationId}] = aniframes;\n`
	code += `}\n`
	//code += "#endif\n"
	return code
}

export default { frameShortCode, framesShortCode, frameLongCode, ledLongCode }
