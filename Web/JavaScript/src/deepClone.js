function deepClone(obj = {}) {
  if (typeof obj !== 'object' || obj === null) {
    return obj;
  }

  let ret;
  if (obj instanceof Array) {
    ret = [];
  } else {
    ret = {};
  }

  for (let key in obj) {
    if (obj.hasOwnProperty(key)) {
      ret[key] = deepClone(obj[key]);
    }
  }

  return ret;
}

const obj1 = {
  name: 'hyc',
  part: [1,2,3],
  frie: {
    key: 111,
    task: {
      pwd: 'root'
    }
  }
};

const obj2 = deepClone(obj1);
obj2.frie.task.pwd = 'home';
obj1.part[0] = 0;
console.log(obj1);
console.log(obj2);