<template>
  <div class="footer">
    <p class="mt-5">EOSIO Account Recovery {{ currentYear }}</p>

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
  height: 110px;
}

</style>
