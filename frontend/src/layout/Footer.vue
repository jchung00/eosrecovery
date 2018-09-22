<template>
  <div class="footer">
    EOSIO Account Recovery {{ currentYear }}
  </div>
</template>

<script>
export default {
  name: 'Footer',
  data () {
    return {
      currentYear: new Date().getFullYear()
    }
  }
}
</script>

<style scoped>
.footer {
  position: absolute;
  text-align: center;
  background-color: #132032;
  color: white;
  width: 100%;
  height: 60px;
}

</style>
