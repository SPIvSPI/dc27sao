<template>
	<div class="container-fluid controls">
		<div class="attrs">
			<button class="btn primary" v-on:click="add">Add Frame</button>&nbsp;
			<button class="btn primary" v-on:click="clear">Clear Frames</button>&nbsp;
			<button class="btn primary" v-on:click="play">Play Animation</button>&nbsp;
			<button class="btn primary" v-on:click="show">Show Code</button>
			<div class="attr">
				<label for="current-frame">Current frame</label>
				<div class="value" id="current-frame">{{ frameNumber }}/{{ frameCount }}</div>
			</div>
			<template v-if="showCode">
				<pre ref="code" class="code">{{ allCode }}</pre>
				<div class="attr">
					<button class="btn primary" v-on:click="copy" style="margin: -5px 0 5px 5px;">Copy Code</button>
				</div>
			</template>
		</div>
	</div>
</template>

<script>
export default {
	name: "app",
	data: function() {
		return {
			showCode: false
		}
	},
	computed: {
		frameCount: function() { return this.$store.getters.frameCount },
		frameNumber: function() { return this.$store.getters.currentFrameNumber },
		allCode: function() { return this.$store.getters.framesShortCode }
	},
	methods: {
		add: function(ev) {
			playsound("/sounds/370846__cabled-mess__funny-click-minimal-ui-sounds.wav")
			this.$store.commit("addFrame")
		},
		clear: function(ev) {
			playsound("/sounds/370846__cabled-mess__funny-click-minimal-ui-sounds.wav")
			var self = this
			this.$bvModal.msgBoxConfirm('Are you sure you want to delete everything?', {
				title: 'Please Confirm',
				size: 'sm',
				buttonSize: 'sm',
				headerVariant: 'danger',
				okVariant: 'danger',
				okTitle: 'Yes',
				cancelTitle: 'No',
				hideHeaderClose: false,
				centered: true
			}).then(function(response) { 
				if (response) {
					playsound("/sounds/370847__cabled-mess__spacey-click-minimal-ui-sounds.wav")
					self.$store.commit("clearFrames")
				}
			}).catch(function(response) {
				console.error(response)
			})
		},
		show: function(ev) {
			playsound("/sounds/370846__cabled-mess__funny-click-minimal-ui-sounds.wav")
			this.showCode = !this.showCode
		},
		copy: function(ev) {
			playsound("/sounds/370848__cabled-mess__tiny-click-minimal-ui-sounds.wav")
			selectElementText(this.$refs.code)
			document.execCommand("copy")
		},
		play: function(ev) {
			playsound("/sounds/370846__cabled-mess__funny-click-minimal-ui-sounds.wav")
			var self = this
			var frameNumber = 0
			var frameCount = this.frameCount
			var timer
			var func = function() {
				if (frameNumber == frameCount) {
					console.log("Animation complete")
					playsound("/sounds/370849__cabled-mess__clack-minimal-ui-sounds.wav")
				} else {
					console.log(`Frame: ${frameNumber}`);
					self.$store.commit("currentFrameNumber", frameNumber)
					var scaling = self.$store.state.timeScalingFactor
					duration = self.$store.getters.duration(frameNumber)
					console.log(`-- waiting for ${duration * scaling} ms (${duration} x ${scaling})`)
					setTimeout(func, duration)
					console.log("-- frame++", frameNumber)
					frameNumber++
				}
			}
			console.log("Animation starting...")
			var duration = this.$store.getters.duration(0)
			timer = setTimeout(func, 0)
		}
	}
}
</script>

<style lang="scss">
.controls {
	/*border: 1px solid blue;*/
}
.attr {
	display: block;
	width: 250px;
}
.attrs {
	label {
		color: #aaa;
		display: inline-block;
		font-size: 14px;
		font-weight: bold;
		margin-top: 10px;
		text-transform: lowercase;
	}

	input {
		background-color: #000;
		border: 0;
		color: #00ff00;
		display: inline-block;
		font-family: Menlo, Consolas, Courier, fixed;
		font-size: 20px;
		margin: 0 10px;
		width: 70px;
	}
}
.value {
	border: 0;
	color: #00ff00;
	display: inline-block;
	font-family: Menlo, Consolas, Courier, fixed;
	font-size: 20px;
	margin: 0 10px;
}
div.controls div.attrs button.btn {
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
pre.code {
	color: #00ff00;
	font-size: 14px;
	padding: 15px;
}
</style>
