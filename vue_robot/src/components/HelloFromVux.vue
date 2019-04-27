<template>
  <div style="display: cell;">
    <div class="pannel">
      <div class="vux-demo">
        <img class="logoup" @click="uup" src="../assets/vux_logo.png">
      </div>
      <div class="middle">
        <div class="left">
          <img class="logoleft" @click="uleft" src="../assets/vux_logo.png">
        </div>
        <div class="right">
          <img class="logoright" @click="uright" src="../assets/vux_logo.png">
        </div>
      </div>
      <div class="vux-demo">
        <img class="logodown" @click="udown" src="../assets/vux_logo.png">
      </div>
    </div>
    <div>
      <group>
        <x-input title="host地址：" v-model="host"></x-input>
      </group>
    </div>
    <div style="margin-top:10px;text-align: center;">
      <x-button type="primary" @click.native="ustop" :mini="true" action-type="button">停止</x-button>
      <!-- <x-button type="warn" :mini=true action-type="button">启动</x-button> -->
    </div>
    <div>
      <group title="发送情况">
        <x-textarea v-model="response"></x-textarea>
      </group>
    </div>
  </div>
</template>

<script>
import { Group, Cell, XButton, XInput, XTextarea } from "vux";

export default {
  components: {
    Group,
    Cell,
    XButton,
    XInput,
    XTextarea
  },
  data() {
    return {
      msg: "Hello World!",
      host: "192.168.31.222",
      response: ""
    };
  },
  methods: {
    ustop: function() {
      if (this.host) {
        this.host = this.host.replace("http://", "");
        this.host = this.host.replace("/", "");
      } else {
        this.host = "192.168.31.222";
      }
      let surl = "http://" + this.host + "/stop";
      console.log(surl);
      this.$jsonp(surl).then(
        function(res) {
          this.response = res.msg;
        },
        error => {
          console.log("出错了");
          this.response = "出错了";
          console.log(error);
        }
      );
    },
    uup: function() {
      if (this.host) {
        this.host = this.host.replace("http://", "");
        this.host = this.host.replace("/", "");
      } else {
        this.host = "192.168.31.222";
      }
      let surl = "http://" + this.host + "/up";
      console.log(surl);
      this.$jsonp(surl).then(
        function(res) {
          this.response = res['msg'];
          console.log(11111);
        },
        error => {
          console.log("出错了");
          this.response = "出错了";
          console.log(error);
        }
      );
    },
    udown: function() {
      if (this.host) {
        this.host = this.host.replace("http://", "");
        this.host = this.host.replace("/", "");
      } else {
        this.host = "192.168.31.222";
      }
      let surl = "http://" + this.host + "/down";
      console.log(surl);
      this.$jsonp(surl).then(
        function(res) {
          this.response = res.msg;
        },
        error => {
          console.log("出错了");
          this.response = "出错了";
          console.log(error);
        }
      );
    },
    uleft: function() {
      if (this.host) {
        this.host = this.host.replace("http://", "");
        this.host = this.host.replace("/", "");
      } else {
        this.host = "192.168.31.222";
      }
      let surl = "http://" + this.host + "/left";
      console.log(surl);
      this.$jsonp(surl).then(
        function(res) {
          this.response = res.msg;
        },
        error => {
          console.log("出错了");
          this.response = "出错了";
          console.log(error);
        }
      );
    },
    uright: function() {
      if (this.host) {
        this.host = this.host.replace("http://", "");
        this.host = this.host.replace("/", "");
      } else {
        this.host = "192.168.31.222";
      }
      let surl = "http://" + this.host + "/right";
      console.log(surl);
      this.$jsonp(surl).then(
        function(res) {
          this.response = res.msg;
        },
        error => {
          console.log("出错了");
          this.response = "出错了";
          console.log(error);
        }
      );
    }
  }
};
</script>

<style>
.pannel {
  width: 100%;
  height: 100%;
  padding: 20px;
  text-align: center;
  vertical-align: center;
}
.vux-demo {
  text-align: center;
  display: inline;
  padding: 0px;
  /* margin-left: 60px; */
}
.logoup {
  width: 100px;
  height: 100px;
  display: inline;
}
.middle {
  display: table;
  width: 100%;
}
.logodown {
  width: 100px;
  height: 100px;
  margin-top: 5px;
  transform: rotate(-180deg);
}
.logoleft {
  width: 100px;
  height: 100px;
  display: table-cell;
  text-align: center;
  vertical-align: center;
  transform: rotate(-90deg);
}
.logoright {
  width: 100px;
  height: 100px;
  display: table-cell;
  text-align: center;
  vertical-align: center;
  transform: rotate(-270deg);
}
.left {
  width: auto;
  display: inline-block !important;
}
.right {
  width: auto;
  display: inline-block !important;
}
</style>
