<template>
	<div>
		<div ref="backing"
			class="led backing"
			v-bind:style="{borderColor: color, left: x + 'px', top: y + 'px'}"
		></div>
		<div ref="led"
			class="led"
			v-bind:data-led="id"
			v-bind:data-state="brightness"
			v-bind:style="{backgroundColor: color, borderColor: color, left: x + 'px', top: y + 'px'}"
			v-on:click="onclick"
		></div>
	</div>
</template>

<script>
export default {
	name: "Led",
	props: {
		id: String,
		overrideX: {type: Number, default: NaN},
		overrideY: {type: Number, default: NaN}
	},
	computed: {
		currentLed: function() { return this.$store.getters.findLed(this.id) },
		color: function() { return this.currentLed.color },
		brightness: function() { return this.currentLed.brightness },
		x: function() { return !isNaN(this.overrideX) ? this.overrideX : this.currentLed.x },
		y: function() { return !isNaN(this.overrideY) ? this.overrideY : this.currentLed.y }
	},
	mounted: function() {
		console.log("Mounted Led", this.id, this.color, this.brightness, this.x, this.y)
	},
	methods: {
		onclick: function(ev) {
			this.$emit("click", this.id, ev)
			playsound("/sounds/370960__cabled-mess__click-02-minimal-ui-sounds.wav")
		}
	}
}
</script>

<style scoped lang="scss">
div.led {
	background-color: #ff0000;
	border-radius: 50%;
	height: 25px;
	position: absolute;
	width: 25px;
	z-index: 999;
	border-style: solid;
	border-width: 1px;
	
	&.backing {
		background-color: #000 !important;
		border-style: solid;
		border-width: 1px;
		box-sizing: border-box;
		z-index: 1 !important;
	}

	&[data-state="0"] { opacity: 1; background-color: #000 !important; }
	&[data-state="1"] { opacity: calc(1/15); }
	&[data-state="2"] { opacity: calc(2/15); }
	&[data-state="3"] { opacity: calc(3/15); }
	&[data-state="4"] { opacity: calc(4/15); }
	&[data-state="5"] { opacity: calc(5/15); }
	&[data-state="6"] { opacity: calc(6/15); }
	&[data-state="7"] { opacity: calc(7/15); }
	&[data-state="8"] { opacity: calc(8/15); }
	&[data-state="9"] { opacity: calc(9/15); }
	&[data-state="10"] { opacity: calc(10/15); }
	&[data-state="11"] { opacity: calc(11/15); }
	&[data-state="12"] { opacity: calc(12/15); }
	&[data-state="13"] { opacity: calc(13/15); }
	&[data-state="14"] { opacity: calc(14/15); }
	&[data-state="15"] { opacity: 1; }
}
</style>
