similar_str.js
==============

Port PHP's [similar_str](https://github.com/php/php-src/blob/2b133e9149eca862c7d8c37f19d95e940970afec/ext/standard/string.c#L3033) function to Node.js

==============

#Example

```javascript
var similar_str = require('./similar_str');
similar_str('123','123'); //100
similar_str('123','1234'); //85.71428571428571
similar_str('hello','hello world'); //62.5

```
