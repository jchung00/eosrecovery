# eosrecovery backend server
## Version : 1.0.0

## Server Info
### required
    mongodb
    redis
    nodejs
### development server info
    http://http://wps-test.hkeos.com

## start
### npm install
    npm install
    npm install -g pm2

### edit nodeos, mongo, redis environment
    vi config/developer.json
    vi tools/create_wps_info.js
    NODE_ENV=developer NODE_PATH=. node tools/create_summary.js

### start pm2
    pm2 start deploy/{eco_xxx.json}

### stop pm2
    pm2 kill


