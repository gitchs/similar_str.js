similar_str.js
==============

Port PHP's [similar_str](https://github.com/php/php-src/blob/2b133e9149eca862c7d8c37f19d95e940970afec/ext/standard/string.c#L3033) function to Node.js

==============

#Example

```javascript
var similarStr = require('./similar-str');
similarStr('123','123'); //100
similarStr('123','1234'); //85.71428571428571
similarStr('hello','hello world'); //62.5

```
