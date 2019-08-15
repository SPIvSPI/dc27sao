<template>
	<div v-bind:class="['frame', {active: isCurrentFrame}]" v-on:click="select">
		<template v-if="show">	
			<div class="attr">
				<div class="label">Animation Id</div>
				<div class="value">{{ animationId }}</div>
			</div>
			<div class="attr">
				<div class="label">Frame Number</div>
				<div class="value">{{ frame.frameNumber }}/{{ frameCount }}</div>
			</div>
			<div class="attr">
				<div class="label">Duration</div>
				<div class="value">
					<input type="text" class="value" v-model="frame.duration"><span class="label">ms <img class="control" src="/img/up.png" v-on:click="incr" /><img class="control" src="/img/down.png" v-on:click="decr" /></span>
				</div>
			</div>
			<div>
				<div class="label">
					Code (
					<a class="toggle" v-on:click="isLong = false" v-bind:style="{color: isLong ? 'inherit' : '#00ff00'}">Short</a> |
					<a class="toggle" v-on:click="isLong = true" v-bind:style="{color: isLong ? '#00ff00' : 'inherit'}">Long</a>
					)
				</div>
				<pre class="code" ref="code" v-if="isLong">{{ longCode }}</pre>
				<pre class="code" ref="code" v-else="isLong">{{ shortCode }}</pre>
			</div>
			<div class="attr">
				<button class="btn primary" v-on:click="copy">Copy Code</button>
			</div>
		</template>
	</div>
</template>

<script>
export default {
	name: "Frame",
	props: {
		frame: Object
	},
	data: function() {
		return {
			isLong: false
		}
	},
	computed: {
		animationId: function() {
			return this.$store.getters.animationId
		},
		show: function() {
			return this.frame && this.frame.leds
		},
		currentSpyColor: function() {
			return this.$store.getters.currentSpyColor
		},
		currentFrameNumber: function() {
			return this.$store.getters.currentFrameNumber
		},
		isCurrentFrame: function() {
			return this.frame.frameNumber === this.currentFrameNumber
		},
		frameCount: function() {
			return this.$store.getters.frameCount
		},
		longCode: function() {
		   return this.$store.getters.frameLongCode()
		},
		shortCode: function() {
			return this.$store.getters.frameShortCode()
		}
	},
	methods: {
		copy: function() {
			selectElementText(this.$refs.code)
			document.execCommand("copy")
		},
		incr: function(ev) {
			ev.stopPropagation()
			playsound("/sounds/370962__cabled-mess__click-01-minimal-ui-sounds.wav")
			var n = parseInt(this.frame.duration) + 1
			n = Math.min(n, 65535)
			this.frame.duration = n.toString(10)
		},
		decr: function(ev) {
			ev.stopPropagation()
			playsound("/sounds/370961__cabled-mess__click-03-minimal-ui-sounds.wav")
			var n = parseInt(this.frame.duration) - 1
			n = Math.max(n, 1)
			this.frame.duration = n.toString(10)
		},
		select: function(ev) {
			console.log("Selected frame", this.frame.frameNumber)
			playsound("/sounds/370848__cabled-mess__tiny-click-minimal-ui-sounds.wav")
			this.$store.commit("currentFrameNumber", this.frame.frameNumber)
		}
	},
	mounted: function() {
		console.log("Mounted Frame", this.frame)
	}
}
</script>

<style scoped lang="scss">
div.frame {
	border-radius: 5px;
	color: #00ff00;
	margin: 3px;
	padding: 5px;
	position: relative;

	&:hover,
	&.active {
		border: 1px solid #00ff00;
		background-color: rgba(0, 255, 0, 0.1);
	}
}
.attr {
	display: block;
	width: 250px;
}
div.label,
span.label {
	color: #aaa;
	display: inline-block;
	font-size: 14px;
	font-weight: bold;
	margin-top: 10px;
	text-transform: lowercase;
}

div.value {
	border: 0;
	color: #00ff00;
	display: inline-block;
	font-family: Menlo, Consolas, Courier, fixed;
	font-size: 20px;
	margin: 0 10px;
}
input.value {
	background-color: #000;
	border: 0;
	color: #00ff00;
	display: inline-block;
	font-family: Menlo, Consolas, Courier, fixed;
	font-size: 14px;
	margin: 0 10px;
	text-align: right;
	width: 60px;
}
a.toggle {
	margin: 5px;
	&:hover, &:active {
		text-decoration: underline !important;
		cursor: pointer;
	}
	&.active {
		text-decoration: underline;
		color: #00ff00;
	}
}
img.control {
	cursor: pointer;
	margin-left: 5px;
	width: 15px;
}
pre.code {
	color: #00ff00;
	font-size: 10px;
	margin-top: 5px;
}
button.btn {
	background-color: #000;
	cursor: pointer;
	color: #00ff00;
	-moz-border-radius: 14px;
	-webkit-border-radius: 14px;
	border-radius: 14px;
	border: 1px solid #00ff00;
	display: inline-block;
	font-family: Menlo, Consolas, Courier, fixed;
	font-size: 10px;
	margin: -5px 0 5px 5px;
	padding: 3px 10px;
	text-decoration: none;
	text-transform: lowercase;

	&:hover {
		background-color: #00ff00;
		color: #000;
	}
	&:active {
		position: relative;
		top: 1px;
	}
}
</style>
