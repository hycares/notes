function Person(name) {
  this.name = name;
}

let p1 = new Person("hyc");

Person.prototype.getName = function() {
  return this.name;
}

Person.prototype.copy = function() {
  return new this.constructor(this.name)
}

function Student(name, score) {
  Person.call(this, name);
  this.score = score;
}

// 通过create继承prototype
Student.prototype = Object.create(Person.prototype);
// 如果不设置constructor那么指向的方法将是父类构造函数
Student.prototype.constructor = Student
Student.prototype.getScore = function() {
  return this.score;
}

let s1 = new Student('hyc', 100);

// es6 语法糖
class Human {
  constructor(name) {
    this.name = name;
  }

  drink() {
    console.log(`${this.name} drink water`);
  }
}

class Male extends Human {
  constructor(name, age) {
    super(name)
    this.age = age;
  }

  Play() {
    console.log('play game');
  }
}

let m = new Male('hyc', 22);