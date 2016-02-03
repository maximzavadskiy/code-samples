'use strict';

// This is my first such interpreter, I did not study compiler theory, so my code is like free-style
//The interpreter is designed in a modular way for easy extension for more operations suppor,
// e.g. it can be easily changed to support nested functions,  variables in functions from other scope,
//scoped operands (e.g. loops), etc.
//I attempted to avoid god-objects by making itemsparsers, each parsing specific operand or operator type  and evaluating it
//Two main parser types used are:
//1) ContextedExpressionParser - this is the main parser, that parses the tokenized expression, using ItemParsers. It chains the operands.
// Also it manages variables and functions
//2) ItemParser - those are main building blocks of the grammar, representing different operands and operators used

class Interpreter {
  constructor () {
    this._parser = new ContextedExpressionParser()
  }

  tokenize (program) {
    if (program === "")
        return [];

    let regex = /\s*(=>|[-+*\/\%=\(\)]|[A-Za-z_][A-Za-z0-9_]*|[0-9]*\.?[0-9]+)\s*/g;
    return program.split(regex).filter(function (s) { return !s.match(/^\s*$/); });
  }
  
  input (expr) {
    try {
      let tokens = this.tokenize(expr);
      //set tokens to the parser before parsing
      this._parser.tokens = tokens

      let val_pos = this._parser.parseValue(0, null);
      if (!val_pos && tokens.length > 0) {
        throw new Error("Unexpected expression beginning")
      } else if (val_pos && val_pos[1] < tokens.length) {//didn't parse all 
        throw new Error("Unexpected end of expression starting with \"" + 
                  tokens[val_pos[1]] + "\" at position "+ val_pos[1] )
      } else {
        return val_pos?val_pos[0].eval():"";
      }
    } catch(e) {
      console.log("While evaluating " + expr)
      throw e
    }
  }
 
}

//parser interface, for readability mostly
class IParser {
  constructor (id, type) {
    this.id = id;
    this.itemType = type;
  }

  parseValue (pos, stack, priority) {
    throw new Error("Calling parseValue in IParser")
  }
}

//expression parser, parsers a list of tokens by chaining the ItemParser
class ContextedExpressionParser extends IParser {

  constructor () {
    super("expression", "expression")

        // this.id = "expression"
    this._MIN_PRIORITY = 100

    this.tokens = []

    this.vars = {};
    this.functions = {};

    this.buildParsers()
  }

  buildParsers () {
    let identifierRegex = /[_a-zA-Z]\w*/
   
    let divisionF = function(str, exp1, exp2) {
      if (exp2 !== 0) {
        return exp1 / exp2;
      } else {
        throw new Error("Zero division")
      }
    }

    //ItemParsers are set here, when evaluating expression they are applied in the order specified,
    //so that the parser will assume the first parser to return the result to be correct parser
    //therefore e.g. FunctionCallParser is before variable_value
    let pIs = [
      ["function-head", /fn/, [], [ "identifier", "argument-list", "fn-operator"], "" , (str, exp1, exp2) => exp2, 0], //{ type : "a"exp2.slice(0,2),
      new FunctionParser(this, this._MIN_PRIORITY-1),
      ["number", /\d+(\.\d+)?/, [], [], "expression" , (str) => parseFloat(str), 0],

      ["identifier", identifierRegex, [], [], "" , (str) => str, 0],

      ["assignment", /\=/, ["identifier"], ["expression"], "expression" , (str, exp1, exp2) => this.setVar(exp1, exp2), 5, "right"],

      new FunctionCallParser(this, 2),
      ["variable_value", null, ["identifier"], [], "expression" , (str, exp1, exp2) => this.getVar(exp1), 1],

            
      ["bracket_expression", /\(/, [], ["expression", "bracket_close"], "expression", (str, exp1, exp2) => exp2[0], this._MIN_PRIORITY-1],
      ["bracket_close", /\)/, [], [], "", null, this._MIN_PRIORITY-1],
      ["fn-operator", /=\>/, [], [], "" , null,  this._MIN_PRIORITY-1],

       
      ["multiplication" , /\*/, ["expression"], ["expression"], "expression", (str, exp1, exp2) => exp1*exp2, 3],
      ["division", /\//, ["expression"], ["expression"], "expression", divisionF, 1],
      ["mod", /\%/, ["expression"], ["expression"], "expression", (str, exp1, exp2) => exp1 % exp2, 3],
      
      ["subtraction", /\-/, ["expression"], ["expression"], "expression", (str, exp1, exp2) => exp1 - exp2, 4],
      ["addition", /\+/, ["expression"], ["expression"], "expression", (str, exp1, exp2) => exp1 + exp2, 4],

      //set priority less than minimum, so that Expression parser will not used them
      new ExpressionListParser("argument-list", this, "identifier", this._MIN_PRIORITY +1),
      new ExpressionListParser("expression-list",this, "expression", this._MIN_PRIORITY+1)
    ]

    
    this._parsers = []
    for (let parserInfo of pIs) {
      //construct default parser from arguments, if nessesary
      let parser =  parserInfo instanceof IParser?parserInfo:ItemParser.makeParser.apply(this, [this].concat(parserInfo));
      this._parsers.push(parser)
    }
  }

  setVar (name, value) {
    //make sure the variable does not exist yet, and not extracted into integer by variable_value parser
    if ((typeof name === "string") &&  !this.functions.hasOwnProperty(name)) {
      this.vars[name] = value
      return value
    } else {
      throw new Error("Variable already defined (tried to assign value \"" + value + "\")")
    }
  }

  getVar (name) {
    if (this.vars.hasOwnProperty(name)) {
      return this.vars[name]
    } else {
      throw new Error("Undefined variable "+ name)
    } 
  }

  makeParsingError (pos, message) {
    return new Error("Unexpected token " + this.tokens[pos] +" at position " + pos + ". " + message)
  }
  
  //common interface with Parser
  parseValue (pos, __stack, priority) {
    if (typeof priority !== "number") priority = this._MIN_PRIORITY

    let stack = []
    let i = pos;
    let lastI = i;
      
    while(true) {
      for (let parser of this._parsers) {
        //if we are parsing first element, priority does not matter (to handle brackets)
        if ( (parser.priority <= this._MIN_PRIORITY) &&
              (i === pos || 
                  parser.priority < priority || 
                  (parser.assotiation === "right" && parser.priority === priority))) {
          
          let val_pos = parser.parseValue(i, stack);
          // only 1 value in stack is supported (1 left operand)
          if (stack.length == 0 && val_pos) {
            i = val_pos[1];
            stack.push(val_pos[0]);
            //do not break here, as other operands might act on already genereted ones e.g. identifier -> variable
          }

          //clear stack from unsuccesfull operand parsing trial
          while(stack.length > 1) stack.pop()
        }
      }
      
      //nothing was parsed
      if (i === lastI) {
        break;
      }
      lastI = i
    }

    if (stack.length === 0) {
      return null
    } else if (stack.length === 1) {
      return [stack.pop(), i]
    } else {
      throw Error("Unexpected expression, stack=", stack)
    }
  }
}

//Item parser, parses one item of particular type, but here also inculding operands (e.g. 1+1 will be one such item)
//Returns a parsed expression that can be evaluated
class ItemParser extends IParser {
  constructor (rootParser, id, regex, parsersBefore, parsersAfter, type, computeF, priority, assotiation) {
    super(id, type)

    this._rp = rootParser;
    this._regex = regex;
    this._parsersBefore = parsersBefore;
    this._parsersAfter = parsersAfter;
    this._computeF = computeF;
    this.priority = priority
    this.assotiation = assotiation
  } 
  
  static makeParser (rootParser, id, regex, parsersBefore, parsersAfter, parserClass, computeF, priority, assotiation) {
    return new ItemParser(rootParser, id, regex, parsersBefore, parsersAfter, parserClass, computeF, priority, assotiation);
  }

  extractLeftOperands (operandIds, stack) {
      let operands = []

      if (stack.length < operandIds.length)
        return null;

      if (stack.length === 0 && operandIds.length === 0)
        return [];

      for (let parserId of operandIds.reverse()) {
        let item = stack.pop();
        operands.push(item)
        if (!item || (item.id != parserId && item.itemType != parserId )) {
          operands.reverse().forEach( (item) => stack.push(item))
          return null;
        }
      }

      return operands
  }

  parseRightOperands (operandIds, i, stack, leftOperands) {
    let rightOperands = []
      let parserObjects = (operandIds || []).map((name) => { 
        return (name === "expression")?this._rp:this._rp._parsers.filter((parser) => parser.id === name)[0]
      })
      
    if (i < this._rp.tokens.length) { 
      for (let parser of parserObjects) {
        let val_pos = parser.parseValue(i, stack, this.priority); // 1+1*5*(1+2)

        if (this.id == 'bracket_expression') {
          let xx = 0
        }
        if (val_pos &&  (val_pos[0].id === parser.id || val_pos[0].itemType === parser.id)) {
          rightOperands.push(val_pos[0]);
          i = val_pos[1]
        } else {
          //recover stack back
          leftOperands.reverse().forEach( (item) => stack.push(item))
          return null
        }
      }
    } else if (parserObjects.length > 0) { 
      leftOperands.reverse().forEach( (item) => stack.push(item))
      return null
    }

    return [rightOperands, i]
  }
  
  parseValue (pos, stack, __priority) {
    let match = null
    if (this._regex == null || (( pos < this._rp.tokens.length) && (match = this._rp.tokens[pos].match("^" + this._regex.source + "$"))) ) {
      //increase only, if an item to be parsed needs to match some operator e.g. +
      if (this._regex) pos++;

      let i = pos;
      //make sure left arguments are correct, remove them from stack
      let leftOperands = this.extractLeftOperands(this._parsersBefore, stack)
      if (leftOperands === null) {
        return null
      }
      
      let val_pos = this.parseRightOperands(this._parsersAfter, i, stack, leftOperands)
      if (val_pos === null)
        return

      let rightOperands  = val_pos[0]
      i = val_pos[1]

      const compact = (arr) => arr.length>1?arr:arr[0];
      //default for simple operands
      let computeF = (this._computeF) || ((str) => str) 
      return  [ new Expression(this.id, match?match[0]:null, compact(leftOperands), compact(rightOperands), computeF, null,  this.itemType), i]
      
    } else {
      return null;
    }
  }
}

class ExpressionListParser extends ItemParser {
  constructor(id, rootParser, itemType, priority ) {
    super()

    this.id = id
    this._rp = rootParser;
    this.priority = priority
    this.itemType = itemType
  }

  parseValue (pos, stack, __priority, itemsLimit) {
    if (pos >= this._rp.tokens.length)
      return null

    let i = pos;
    let val_pos = null;
    let argList = []

    let parser = null;
    if (this.itemType === "expression") {
      parser = this._rp
    } else {
      parser = this._rp._parsers.filter((parser) => parser.id === this.itemType)[0]
    }

    //priority must be less than initial to avoid circular recursion
    while( i < this._rp.tokens.length && 
          ((typeof itemsLimit !== 'number')|| argList.length < itemsLimit) &&
          (val_pos = parser.parseValue(i, stack, this.priority-1) ) ) {
      argList.push(val_pos[0])
      i = val_pos[1]
    } 

    return [new Expression(this.id, "", argList, "", (str, exp, exp2) => exp), i] 
  }

}


class FunctionParser extends ItemParser {
  constructor (rootParser, priority ) {
    super()

    this.id = "function-body"
    this.itemType = "function-body"

    this.priority = priority
    this._rp = rootParser
    this.tokens = this._rp.tokens
  }

  parseValue (pos, stack, __priority) {

    let functionHead = this.extractLeftOperands(["function-head"], stack)
    if (functionHead && functionHead.length === 1) {
        functionHead = functionHead[0]
        let args = functionHead.eval()

        let funcInterpreter = new ContextedExpressionParser()
        funcInterpreter.tokens = this._rp.tokens

        let val_pos = funcInterpreter.parseValue(pos, null, this.priority)

        if (val_pos) {
          pos = val_pos[1]
          return [new FunctionExpression("function", funcInterpreter, args, val_pos[0], null,  this._rp), pos]
        } else {
          //a bit of a hack here since function-head can be used somewhere else too
          throw new Error("Function definition of \"" + functionHead.exp1 +"\" is missing body")
        }
     }
  }
}

class FunctionCallParser extends ItemParser {
  constructor (rootParser, priority ) {
    super()

    this.id = "function-call"
    this.itemType = "expression"
    this.priority = priority
    this._rp = rootParser
    this.tokens = this._rp.tokens
 }

  parseValue (pos, stack, priority) {

    let identifier = this.extractLeftOperands(["identifier"], stack) 
    if (identifier) {
      identifier = identifier[0]
      if ( this._rp.functions.hasOwnProperty(identifier.eval()) ) {
        let funcName = identifier.eval()

        let funcArgs = this._rp.functions[funcName].args

        let paramValuesParser = this._rp._parsers.filter((parser) => parser.id === "expression-list")[0]
        let val_pos = paramValuesParser.parseValue(pos, null , null, funcArgs.length)
      
        let paramValues = []
        if (val_pos) {
          paramValues = val_pos[0].eval()
          pos = val_pos[1]
        }

        if (!val_pos && funcArgs.length === 0 || paramValues && paramValues.length === funcArgs.length) {
          
          let callFunctionF = function(str, exp1, exp2) {
            let funcInterpreter = this._rp.functions[funcName].interpreter

            funcArgs.forEach( (argName, i) => {
              funcInterpreter.vars[argName] = paramValues[i] 
            })

            try {
              return  this._rp.functions[funcName].body.eval()
            } catch(e) {
              console.error("In function " + str);
              throw e;
            }
          }

          return [new Expression("function-call", funcName, funcArgs, new NoAutomaticEvalExpression(this._rp.functions[funcName].body), callFunctionF,  this._rp), pos]
        } else {
          stack.push(identifier)
          return null;
        }
          
      } else {
        stack.push(identifier)
        return null;
      }
    } else {
      return null
    }
  }

}


class Expression  {
  
  constructor (id, str, exp1, exp2, computeF, rootParser, itemType) {
    this.id = id
    this.str = str
    this.exp1 = exp1
    this.exp2 = exp2
    this.computeF = computeF
    this._rp = rootParser
    this.itemType = itemType
  }

  static evalOrValue (exp) {
    if ( exp && (exp.eval || Array.isArray(exp)) ) {
      if (exp.eval) {
        return exp.eval()
      } else { 
        return exp.map( item => Expression.evalOrValue(item))
      }
    } else {
      return exp
    }
  }

  eval() {
    return this.computeF(this.str, Expression.evalOrValue(this.exp1), Expression.evalOrValue(this.exp2))
  }
}

class FunctionExpression extends Expression {
  eval() {
    let functionInterpreter = this.str
    let functionName = this.exp1[0];
    let functionArgs = this.exp1[1];
    let functionBody = this.exp2;

    if (!this._rp.vars.hasOwnProperty(functionName)) {
      if ( functionArgs.length !== functionArgs.filter((elem, pos) => functionArgs.indexOf(elem) == pos).length) {
        throw new Error("Function declaration of \"" + functionName+ "\" contains duplicate parameter variables")
      }

      let findUndefinedVariable = function(exp, funcArgs) {
        if (exp.id === "variable_value") {
          if ( funcArgs.indexOf(exp.exp1.eval()) == -1) {
            return exp.exp1.eval();
          } else 
            return null
        } else {
          let undefinedVar = null
          if (exp.exp1 && (undefinedVar = findUndefinedVariable(exp.exp1, funcArgs)))
            return undefinedVar

          else if (exp.exp2 && (undefinedVar = findUndefinedVariable(exp.exp2, funcArgs)))
            return undefinedVar

          else
            return null;
        }
      }

      let undefinedVar = findUndefinedVariable(functionBody, functionArgs)
      if (undefinedVar) {
        throw new Error("Cannot declare function \"" + functionName + "\" Variable \""+ undefinedVar +"\" is not declared")
      } else {

        this._rp.functions[functionName] = { args: functionArgs, body: functionBody, interpreter: functionInterpreter }
        return ""
      }
    } else {
      throw new Error("Cannot declare function \"" + functionName + "\" Variable with such a name already exist")
    }
  }
}

class NoAutomaticEvalExpression extends Expression {
  constructor(expression) {
    super()
    this.exp = expression
  }
  eval() {
    return this.expression
  }
}
