#include <node.h>
#include <v8.h>

using namespace v8;

static void similar_str(const char *txt1, int len1, const char *txt2, int len2, int *pos1, int *pos2, int *max);
static int similar_char(const char *txt1, int len1, const char *txt2, int len2);


Handle<Value> Method(const Arguments& args) {
  HandleScope scope;
  if (args.Length() != 2) {
    ThrowException(Exception::TypeError(String::New("Wrong number of arguments")));
    return scope.Close(Undefined());
  }
  if (!args[0]->IsString() || !args[1]->IsString()){
    ThrowException(Exception::TypeError(String::New("arguments should be instance of String")));
    return scope.Close(Undefined()); 
  }

  String::Utf8Value str1(args[0]);
  String::Utf8Value str2(args[1]);

  int len1 = str1.length();
  int len2 = str2.length();

  if (!len1 || !len2){
    return scope.Close(Number::New(0.0)); 
  } else {
    int sum = similar_char(*str1,len1,*str2,len2);
    double sim = sum * 200.0 / (len1 + len2);
    return scope.Close(Number::New(sim));
  }
}

void init(Handle<Object> exports) {
  exports->Set(String::NewSymbol("similar_str"),
      FunctionTemplate::New(Method)->GetFunction());
}


static void similar_str(
  const char *txt1, int len1,
  const char *txt2, int len2,
  int *pos1, int *pos2,
  int *max){

  char *p, *q;
  char *end1 = (char *) txt1 + len1;
  char *end2 = (char *) txt2 + len2;
  int l;

  *max = 0;
  for (p = (char *) txt1; p < end1; p++) {
    for (q = (char *) txt2; q < end2; q++) {
      for (l = 0; (p + l < end1) && (q + l < end2) && (p[l] == q[l]); l++);
      if (l > *max) {
        *max = l;
        *pos1 = p - txt1;
        *pos2 = q - txt2;
      }
    }
  }
}


static int similar_char(
  const char *txt1, int len1,
  const char *txt2, int len2){

  int sum;
  int pos1 = 0, pos2 = 0, max;

  similar_str(txt1, len1, txt2, len2, &pos1, &pos2, &max);
  if ((sum = max)) {
    if (pos1 && pos2) {
      sum += similar_char(
        txt1, pos1,
        txt2, pos2);
    }
    if ((pos1 + max < len1) && (pos2 + max < len2)) {
      sum += similar_char(
        txt1 + pos1 + max, len1 - pos1 - max,
        txt2 + pos2 + max, len2 - pos2 - max);
    }
  }

  return sum;
}


NODE_MODULE(similar_str, init)