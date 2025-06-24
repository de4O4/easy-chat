const config_module = require('./config.json');
const redis = require('ioredis');

const RedisCli = new redis({
    host: config_module.redis.host,
    port: config_module.redis.port,
    password: config_module.redis.passwd,
});

RedisCli.on("error", function(err){                 //监听错误信息
    console.log("Redis connection error: " + err);
 //   RedisCli.quit();
});


async function GetRedis(key){
    try {
        const result = await RedisCli.get(key);
        if(result === null) {
            console.log(`Key ${key} not found in Redis`);
            return null;
        }
        console.log(`Key ${key} found in Redis`);
        return result;
        
    } catch (error) {
        console.log(`Error retrieving key ${key} from Redis: ${error}`);
        return null;
    }
}


async function QueryRedis(key){                     //查询key是否在redis中
    try {
        const result = await RedisCli.exists(key);
        if(result == 0){
            console.log(`Key ${key} does not exist in Redis`);
            return null;
        }
        console.log(`Key ${key} exists in Redis`);
        return result;
    } catch (error) {
        console.log(`Error checking key ${key} in Redis: ${error}`);
        return null;
    }
}


async function SetRedisExpire(key , value , expiretime){                //设置key的值和过期时间
    try {
        await RedisCli.set(key, value);                     //设置key的值
        await RedisCli.expire(key, expiretime);             //设置过期时间
        return true;
    } catch (error) {
        console.log(`Error setting key ${key} in Redis: ${error}`);
        return false;   
    }
}


function Quit(){
    RedisCli.quit();                                      //关闭redis连接
    console.log("Redis connection closed");
}

module.exports = {
    GetRedis,
    QueryRedis,
    SetRedisExpire,
    Quit
};