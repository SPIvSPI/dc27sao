import Vue from 'vue'
import App from './App.vue'

import store from "./store"

import BootstrapVue from 'bootstrap-vue'
Vue.use(BootstrapVue)
import 'bootstrap/dist/css/bootstrap.css'
import 'bootstrap-vue/dist/bootstrap-vue.css'

Vue.config.productionTip = false

new Vue({
	store,
	render: function (h) { return h(App) },
}).$mount('#app')
