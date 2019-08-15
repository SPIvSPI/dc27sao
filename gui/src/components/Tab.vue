<template>
	<div class="container-fluid tab">
		<div class="row">
			<div class="col-2" style="max-height: 1024px; overflow-y: scroll;">
				<frames />
			</div>
			<div class="col-10">
				<controls v-on:play="play" />
				<spy />
			</div>
		</div>
	</div>
</template>

<script>
import Controls from "./Controls.vue"
import Spy from "./Spy.vue"
import Frames from "./Frames.vue"

function ghettoCopy(obj) {
	return JSON.parse(JSON.stringify(obj))
}

export default {
	name: "Tab",
	data: function() {
		return {
			init: false,
			internalFrames: [],
			currentFrame: 0
		}
	},
	computed: {
		currentSpyColor: function() { return this.$store.getters.currentSpyColor }
	},
	methods: {
		play: function(state) {
			console.log("Play")
		}
	},
	components: { Controls, Spy, Frames }
}
</script>

<style scoped lang="scss">
div.tab {
	/*	border: 1px solid red;*/
}
</style>
