// The Vue build version to load with the `import` command
// (runtime-only or standalone) has been set in webpack.base.conf with an alias.
import Vue from 'vue'
import FastClick from 'fastclick'
import VueRouter from 'vue-router'
import App from './App'
import Home from './components/HelloFromVux'
import Vuex from 'vuex'
import { sync } from 'vuex-router-sync'
import { AjaxPlugin,ConfigPlugin } from 'vux'
import vuexI18n from 'vuex-i18n'
import  VueJsonp  from  'vue-jsonp'
// import VeeValidate from 'vee-validate';
// Vue.use(VeeValidate)
Vue.use(VueJsonp)
Vue.use(AjaxPlugin)
Vue.use(VueRouter)
Vue.use(Vuex)
const routes = [{
  path: '/',
  component: Home
}]

const router = new VueRouter({
  routes
})

FastClick.attach(document.body)
/** i18n **/
let store = new Vuex.Store({
  modules: {
    i18n: vuexI18n.store
  }
})

Vue.use(vuexI18n.plugin, store)
Vue.config.productionTip = false
sync(store, router)
// global VUX config
Vue.use(ConfigPlugin, {
  $layout: 'VIEW_BOX' // global config for VUX, since v2.5.12
})

/* eslint-disable no-new */
new Vue({
  router,
  render: h => h(App)
}).$mount('#app-box')
