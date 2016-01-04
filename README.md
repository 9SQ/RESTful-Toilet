#RESTful-Toilet

RESTful-Toilet is a best solution for using smart phone while using Washlet(R).

**This is IoT (Internet of Toilet)**

## Description

トイレ中もスマホを手放せない人のために、スマホでウォシュレット(R)を制御可能にするシステムです。

詳細は[ブログの記事](http://eleclog.quitsq.com/2016/01/restful-toilet.html)を参照してください。

ウォシュレットはTOTO株式会社の登録商標です。

## How to use

1. ESP-WROOM-02に赤外線LEDを接続する
2. プログラムを書き込む
3. 電源を供給してあげる

起動すると http://toilet.local で制御を待ち受けます。
スマホなどで普通にアクセスするとボタンが表示されるので、押せばその通りに動作します。
(後ろではXHRでAPIを叩いているだけです)

APIを直接叩きたい人は以下を参照してください。

## Example Requests

**おしりを洗浄したい時**

```sh
curl -X POST -d 'c=rear' http://toilet.local/washlet
```

**洗浄をやめたい時**

```sh
curl -X POST -d 'c=stop' http://toilet.local/washlet
```

**大を流す時**

```sh
curl -X DELETE -d 'c=big' http://toilet.local/washlet
```

流す動作だけ**DELETE**なのでご注意ください。

## Requirements

* [Arduino core for ESP8266 WiFi chip](https://github.com/esp8266/Arduino)
* [IRremoteESP8266](https://github.com/markszabo/IRremoteESP8266)