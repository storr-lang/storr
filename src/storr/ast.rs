/// BNF Grammar:
///
/// ```bnf
/// <program>         ::= <statement>* "\0"
///
/// <statement>       ::= <assignment> "\n"
///
/// <assignment>      ::= <function> ["(" <parameters> ")"] ":=" <expression>
///
/// <function>        ::= String
///
/// <parameters>      ::= <parameter> ("," <parameter>)*
///
/// <parameter>       ::= String
///
/// <expression>      ::= <literal>
///                     | <binary>
///                     | <unary>
///                     | <call>
///                     | <match>
///                     | "(" <expression> ")"
///                     | "[" <expression> "]"
///                     | "{" <expression> "}"
///
/// <literal>         ::= <variable> | <integer> | <floating point> | <boolean> | Nothing
///
/// <variable>        ::= String
///
/// <integer>         ::= i64
///
/// <floating point>  ::= f64
///
/// <boolean>         ::= bool
///
/// <binary>          ::= <left> <binary operator> <right>
///
/// <left>            ::= <expression>
///
/// <binary operator> ::= "+"
///                     | "-"
///                     | "*"
///                     | "/"
///                     | "%"
///                     | "^"
///                     | "="
///                     | "!="
///                     | "<"
///                     | ">"
///                     | "<="
///                     | ">="
///                     | "&"
///                     | "|"
///                     | "!&"
///                     | "!|"
///
/// <right>           ::= <expression>
///
/// <unary>           ::= <unary operator> <operand>
///
/// <unary operator>  ::= "-" | "!"
///
/// <operand>         ::= <expression>
///
/// <call>            ::= <function> "(" <arguments> ")"
///
/// <arguments>       ::= <argument> ("," <argument>)*
///
/// <argument>        ::= <expression>
///
/// <match>           ::= "{" <cases> "}"
///
/// <cases>           ::= <case> ("," <case>)*
///
/// <case>            ::= <pattern> "=>" <expression>
///
/// <pattern>         ::= <literal> ("," <literal>)*
/// ```
///

pub struct Program {
    pub statements: Vec<Statement>,
}

pub enum Statement {
    Assignment {
        function: String,
        parameters: Vec<String>,
        expression: Expression,
    },
}

pub enum Expression {
    Literal(Literal),
    Binary {
        left: Box<Expression>,
        operator: BinaryOperator,
        right: Box<Expression>,
    },
    Unary {
        operator: UnaryOperator,
        operand: Box<Expression>,
    },
    Call {
        function: String,
        arguments: Vec<Expression>,
    },
    Match {
        cases: Vec<Case>,
    },
}

pub enum Literal {
    Variable(String),
    Integer(i64),
    FloatingPoint(f64),
    Boolean(bool),
    Nothing,
}

pub enum BinaryOperator {
    Plus,
    Minus,
    Asterisk,
    Slash,
    Percent,
    Caret,
    Equal,
    NotEqual,
    LessThan,
    GreaterThan,
    LessThanEqual,
    GreaterThanEqual,
    And,
    Or,
    NotAnd,
    NotOr,
}

pub enum UnaryOperator {
    Minus,
    Not,
}

pub struct Case {
    pattern: Vec<Literal>,
    expression: Expression,
}
