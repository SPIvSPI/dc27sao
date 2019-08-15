<template>
	<div class="frames">
		<frame v-for="frame in frames" v-bind:frame="frame" v-bind:key="frame.color + '.' + frame.animationId + '.' + frame.frameNumber" />
	</div>
</template>

<script>
import Frame from "./Frame.vue"

export default {
	name: "Frames",
	computed: {
		frames: function() { return this.$store.getters.frames }
	},
	methods: {
		select: function(frame) {
			console.log("Selected", frame)
		}
	},
	mounted: function() {
		console.log("Frames mounted", this.frames)
	},
	components: { Frame }
}
</script>

<style scoped lang="scss">
div.frames {
	height: 100%;
}
</style>
