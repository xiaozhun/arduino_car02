<template>
  <div id="app" style="height:100%;">
    <view-box>
      <router-view class="router-view"></router-view>
      <tabbar class="vux-demo-tabbar" icon-class="vux-center"  slot="bottom">
          <tabbar-item :link="{path:'/'}" :selected="this.$route.path === '/'">
            <span class="demo-icon-22 vux-demo-tabbar-icon-home" slot="icon" style="position:relative;top: -2px;">&#xe637;</span>
            <span slot="label">小车</span>
          </tabbar-item>
          <tabbar-item :link="{path:'/demo'}" :selected="isDemo" badge="9">
            <span class="demo-icon-22" slot="icon">&#xe633;</span>
            <span slot="label"><span v-if="componentName" class="vux-demo-tabbar-component">主页</span><span v-else>Demos</span></span>
          </tabbar-item>
        </tabbar>
    </view-box>
  </div>
</template>

<script>
import { Radio, Group, Cell, Badge, Drawer, Actionsheet, ButtonTab, ButtonTabItem, ViewBox, XHeader, Tabbar, TabbarItem, Loading, TransferDom } from 'vux'
import { mapState, mapActions } from 'vuex'
export default {
  name: 'app',
  components: {
    Radio,
    Group,
    Cell,
    Badge,
    Drawer,
    ButtonTab,
    ButtonTabItem,
    ViewBox,
    XHeader,
    Tabbar,
    TabbarItem,
    Loading,
    Actionsheet
  },
  computed:{
    // ...mapState({
    //   route: state => state.route,
    //   path: state => state.route.path,
    //   deviceready: state => state.app.deviceready,
    //   demoTop: state => state.vux.demoScrollTop,
    //   isLoading: state => state.vux.isLoading,
    //   direction: state => state.vux.direction
    // }),
    isShowBar () {
      if (this.entryUrl.indexOf('hide-tab-bar') > -1) {
        return false
      }
      return true
    },
    isDemo () {
      return false
    },
    componentName () {
      // if (this.route.path) {
      //   const parts = this.route.path.split('/')
      //   if (/component/.test(this.route.path) && parts[2]) return parts[2]
      // }
      return 'all'
    },
  },
  data () {
    return {
      entryUrl: document.location.href,
      showMenu: false,
      menus: {
        'language.noop': '<span class="menu-title">Language</span>',
        'zh-CN': '中文',
        'en': 'English'
      },
      drawerVisibility: false,
      showMode: 'push',
      showModeValue: 'push',
      showPlacement: 'left',
      showPlacementValue: 'left'
    }
  }
}
</script>

<style lang="less">
@import '~vux/src/styles/reset.less';
@import '~vux/src/styles/1px.less';
@import '~vux/src/styles/tap.less';
body {
  background-color: #fbf9fe;
}
html, body {
  height: 100%;
  width: 100%;
  overflow-x: hidden;
}

.demo-icon-22 {
  font-family: 'vux-demo';
  font-size: 22px;
  color: #888;
}
.weui-tabbar.vux-demo-tabbar {
  /** backdrop-filter: blur(10px);
  background-color: none;
  background: rgba(247, 247, 250, 0.5);**/
}
.vux-demo-tabbar .weui-bar__item_on .demo-icon-22 {
  color: #F70968;
}
.vux-demo-tabbar .weui-tabbar_item.weui-bar__item_on .vux-demo-tabbar-icon-home {
  color: rgb(53, 73, 94);
}
.demo-icon-22:before {
  content: attr(icon);
}
.vux-demo-tabbar-component {
  background-color: #F70968;
  color: #fff;
  border-radius: 7px;
  padding: 0 4px;
  line-height: 14px;
}
.weui-tabbar__icon + .weui-tabbar__label {
  margin-top: 0!important;
}
.vux-demo-header-box {
  z-index: 100;
  position: absolute;
  width: 100%;
  left: 0;
  top: 0;
}

@font-face {
  font-family: 'vux-demo';  /* project id 70323 */
  src: url('//at.alicdn.com/t/font_70323_wlronpvr565yiudi.eot');
  src: url('//at.alicdn.com/t/font_70323_wlronpvr565yiudi.eot?#iefix') format('embedded-opentype'),
  url('//at.alicdn.com/t/font_70323_wlronpvr565yiudi.woff') format('woff'),
  url('//at.alicdn.com/t/font_70323_wlronpvr565yiudi.ttf') format('truetype'),
  url('//at.alicdn.com/t/font_70323_wlronpvr565yiudi.svg#iconfont') format('svg');
}

.demo-icon {
  font-family: 'vux-demo';
  font-size: 20px;
  color: #04BE02;
}

.demo-icon-big {
  font-size: 28px;
}

.demo-icon:before {
  content: attr(icon);
}

.router-view {
  width: 100%;
  top: 46px;
}
.vux-pop-out-enter-active,
.vux-pop-out-leave-active,
.vux-pop-in-enter-active,
.vux-pop-in-leave-active {
  will-change: transform;
  transition: all 500ms;
  height: 100%;
  top: 46px;
  position: absolute;
  backface-visibility: hidden;
  perspective: 1000;
}
.vux-pop-out-enter {
  opacity: 0;
  transform: translate3d(-100%, 0, 0);
}
.vux-pop-out-leave-active {
  opacity: 0;
  transform: translate3d(100%, 0, 0);
}
.vux-pop-in-enter {
  opacity: 0;
  transform: translate3d(100%, 0, 0);
}
.vux-pop-in-leave-active {
  opacity: 0;
  transform: translate3d(-100%, 0, 0);
}
.menu-title {
  color: #888;
}
</style>
