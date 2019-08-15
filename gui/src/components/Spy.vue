<template>
	<div class="row">
		<div class="col-4 spy">
			<div v-bind:class="['spy', currentSpyColor]">
				<img class="spy" v-bind:src="image" />
				<template v-for="led in leds">
					<led v-bind="led" v-bind:key="led.id" v-on:click="onclick" />
				</template>
			</div>
		</div>
		<div class="col-6 info">
			<info v-bind:led="selected" />
		</div>
	</div>
</template>

<script>
import Led from "./Led.vue"
import Info from "./Info.vue"

export default {
	name: "Spy",
	data: function() {
		return {
			selected: {id:""}
		}
	},
	computed: {
		animationId: function() {
			return this.$store.getters.animationId
		},
		frameNumber: function() {
			return this.$store.getters.currentFrameNumber
		},
		currentSpyColor: function() {
			return this.$store.getters.currentSpyColor
		},
		image: function() { 
			return `/img/${this.currentSpyColor}-spy.png`
		},
		leds: function() {
			return this.$store.getters.currentFrame.leds
		}
	},
	watch: {
		frameNumber: function() {
			var id = this.selected.id
			if (id) {
				this.selected = this.find(id) || {id: ""}
			}
		},
		currentSpyColor: function() {
			var id = this.selected.id
			if (id) {
				this.selected = this.find(id) || {id: ""}
			}
		}
	},
	methods: {
		find: function(id) {
			for (var i in this.leds) {
				var led = this.leds[i]
				if (led.id === id) {
					return led
				}
			}
		},
		onclick: function(id, ev) {
			console.log("Selected", id, ev)
			this.selected = this.find(id)
		}
	},
	components: {
		Led,
		Info
	}
}
</script>

<style scoped lang="scss">

@import url(https://fonts.googleapis.com/css?family=VT323);

div.spy {
	min-width: 430px;
	position: relative;
}
img.spy {
	width: 400px;
}
</style>
