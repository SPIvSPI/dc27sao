<template>
	<div class="info">
		<template v-if="led.id">
			<div class="title">
				<led v-bind:id="led.id" v-bind:color="led.color" v-bind:brightness="led.brightness" v-bind:overrideX="5" v-bind:overrideY="5"/>
				<div class="led-label" v-bind:style="{color: led.color}">LED-{{ led.id }}</div>
			</div>
			<div class="label">Brightness</div>
			<input type="text" v-model="led.brightness"></input>
			<img class="control" src="/img/up.png" v-on:click="incr" />
			<img class="control" src="/img/down.png" v-on:click="decr" />
			&nbsp;&nbsp;(<a v-on:click="fullyon">fully on</a>|<a v-on:click="fullyoff">fully off</a>)
			<div class="label">Code</div>
			<pre ref="code">{{ code }}</pre>
			<div class="attr">
				<button class="btn primary" v-on:click="copy" style="margin: 0 0 5px 5px;">Copy Code</button>
			</div>
		</template>
	</div>
</template>

<script>
import Led from "./Led.vue"

export default {
	name: "Info",
	props: {
		led: Object
	},
	computed: {
		animationId: function() {
			return this.$store.getters.animationId
		},
		frameNumber: function() {
			return this.$store.getters.currentFrameNumber
		},
		code: function() {
			if (this.led.id) {
				return this.$store.getters.currentFrameLedLongCode(this.led.id)
			}
		}
	},
	methods: {
		fullyon: function() {
			playsound("/sounds/370962__cabled-mess__click-01-minimal-ui-sounds.wav")
			this.led.brightness = 15
			var self = this
			if (this.led.aliases) {
				this.led.aliases.forEach(function(id) {
					self.$store.getters.findLed(id).brightness = 15
				})
			}
		},
		fullyoff: function() {
			playsound("/sounds/370961__cabled-mess__click-03-minimal-ui-sounds.wav")
			this.led.brightness = 0
			var self = this
			if (this.led.aliases) {
				this.led.aliases.forEach(function(id) {
					self.$store.getters.findLed(id).brightness = 0
				})
			}
		},
		incr: function(ev) {
			if (this.led.id) {
				playsound("/sounds/370962__cabled-mess__click-01-minimal-ui-sounds.wav")
				var n = parseInt(this.led.brightness) + 1
				n = Math.min(n, 15)
				this.led.brightness = n
				var self = this
				if (this.led.aliases) {
					this.led.aliases.forEach(function(id) {
						self.$store.getters.findLed(id).brightness = n
					})
				}
			}
		},
		decr: function(ev) {
			if (this.led.id) {
				playsound("/sounds/370961__cabled-mess__click-03-minimal-ui-sounds.wav")
				var n = parseInt(this.led.brightness) - 1
				n = Math.max(n, 0)
				this.led.brightness = n
				var self = this
				if (this.led.aliases) {
					this.led.aliases.forEach(function(id) {
						self.$store.getters.findLed(id).brightness = n
					})
				}
			}
		},
		copy: function(ev) {
			playsound("/sounds/370848__cabled-mess__tiny-click-minimal-ui-sounds.wav")
			selectElementText(this.$refs.code)
			document.execCommand("copy")
		}
	},
	components: { Led }
}
</script>

<style scoped lang="scss">
div.info {
	/*border: 1px solid purple;*/
	background-color: #000;
	color: #00ff00;
}
div.title {
	height: 40px;
	top: 20px;
	width: 100%;
	position: relative;
}
div.label {
	color: #aaa;
	font-size: 14px;
	font-weight: bold;
	margin-top: 40px;
	text-transform: lowercase;
}

div.led-label {
	font-family: Menlo, Consolas, Courier, fixed;
	font-size: 32px;
	font-weight: bold;
	left: 35px;
	position: absolute;
	top: -2px;
}
div.info pre {
	color: #00ff00;
	font-size: 14px;
	margin: 0;
	padding: 10px;
}
div.info div.code-container {
	left: 360px;
	position: absolute;
	top: 10px;
}
input {
	background-color: #000;
	border: 0;
	color: #00ff00;
	font-family: Menlo, Consolas, Courier, fixed;
	font-size: 20px;
	margin: 0 10px;
	width: 30px;
}
img.control {
	cursor: pointer;
	margin-left: 5px;
	width: 20px;
}
a {
	font-size: 16px;
	margin: 0 10px;
	&:hover {
		text-decoration: underline !important;
		cursor: pointer;
	}
}
button.btn {
	text-transform: lowercase;
	background-color: #000;
	-moz-border-radius: 14px;
	-webkit-border-radius: 14px;
	border-radius: 14px;
	border: 1px solid #00ff00;
	display: inline-block;
	cursor: pointer;
	color: #00ff00;
	font-family: Menlo, Consolas, Courier, fixed;
	font-size: 13px;
	padding: 3px 10px;
	text-decoration: none;

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
