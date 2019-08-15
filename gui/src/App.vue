<template>
	<div class="container-fluid">
		<div class="row">
			<div class="col-8">
				<a v-for="tab in tabs"
					v-bind:key="tab.name"
					v-bind:class="['tab', { active: currentTab === tab }]"
					v-on:click="select(tab)"
				>{{ tab.name }}-spi</a>
			</div>
			<div class="col-4 header-attrs">
				<div class="row">
					<div class="col-6">
						<div class="header-attr">
							<label for="animation-id">Animation Id</label>
							<input id="animation-id" type="text" v-model="animationId"></input>
						</div>
					</div>
					<div class="col-6">
						<div class="header-attr">
							<label for="timeScaling">Time Scaling Factor</label>
							<input id="timeScaling" type="text" v-model="timeScalingFactor"></input>
						</div>
					</div>
				</div>
			</div>
		</div>
		<div class="row">
			<component v-bind:is="currentTab.component" class="tab" v-bind:spyColor="currentTab.name" />
		</div>
	</div>
</template>

<script>
import Tab from "./components/Tab.vue"

const tabs = [
	{name: "white", component: Tab},
	{name: "black", component: Tab}
]

export default {
	name: "app",
	data: function() {
		return {
			tabs: tabs,
			currentTab: tabs[0]
		}
	},
	computed: {
		animationId: {
			get: function() { return this.$store.getters.animationId },
			set: function(value) { this.$store.commit("animationId", value) }
		},
		timeScalingFactor: {
			get: function() { return this.$store.getters.timeScalingFactor },
			set: function(value) { this.$store.commit("timeScalingFactor", value) }
		}
	},
	watch: {
		currentTab: function() {
			this.$store.commit("currentSpyColor", this.currentTab.name)
		}
	},
	methods: {
		select: function(tab) {
			playsound("/sounds/370846__cabled-mess__funny-click-minimal-ui-sounds.wav")
			this.currentTab = tab
		}
	},
	mounted: function() {
		console.log("App mounted")
	},
	components: { Tab }
}
</script>

<style lang="scss">
html,
body {
	margin: 0; 
	padding: 0;
	color: #fff;
	background-color: #000;
}
a.tab {
	color: #aaa;
	font-family: Menlo, Consolas, Courier, fixed;
	font-size: 32px;
	margin: 15px;
	&:hover {
		text-decoration: underline !important;
	}
	&.active {
		color: #00ff00 !important;
		font-weight: bold;
	}	
}
div.container-fluid {
	background-color: #000;
	color: #aaa;
	font-family: 'Avenir', Helvetica, Arial, sans-serif;
	-webkit-font-smoothing: antialiased;
	-moz-osx-font-smoothing: grayscale;
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
.header-attr {
	display: inline-block;
	margin: 0 10px;
	width: 250px;
}
.header-attrs {
	padding-right: 15px;
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
</style>
