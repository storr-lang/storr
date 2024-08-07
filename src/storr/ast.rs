/// BNF Grammar:
///
/// <program>    ::= <statement>* "\0"
///
/// <statement>  ::= <assignment> "\n"
///
/// <assignment> ::= <identifier> <parameters> ":=" <expression>
///
/// <identifier> ::= String
///
/// <parameters> ::= <identifier> ("," <identifier>)*
///
/// <expression> ::= <literal>
///                | <binary>
///                | <unary>
///                | <call>
///                | <match>
///                | "(" <expression> ")"
///                | "[" <expression> "]"
///                | "{" <expression> "}"
///
/// <literal>    ::= <identifier> | Integer | FloatingPoint | Boolean | Nothing
///
/// <identifier> ::= String
///
/// <binary>     ::= <expression> <binary operator> <expression>
///
/// <binary operator> ::= "+" | "-" | "*" | "/" | "%" | "^" | "=" | "!=" | "<" | ">" | "<=" | ">=" | "&" | "|" | "!&" | "!|"
///
/// <unary>      ::= <unary operator> <expression>
///
/// <unary operator> ::= "-" | "!"
///
/// <call>       ::= <identifier> <arguments>
///
/// <arguments>  ::= <expression> ("," <expression>)*
///
/// <match>      ::= "{" <cases> "}"
///
/// <cases>      ::= <case> ("," <case>)*
///
/// <case>       ::= <pattern> "=>" <expression>
///
/// <pattern>    ::= <literal> ("," <literal>)*
///

pub struct Program {
    pub statements: Vec<Statement>,
}
impl Program {
    pub fn to_string(&self) -> String {
        self.statements
            .iter()
            .map(|stmt| stmt.to_string())
            .collect::<Vec<_>>()
            .join("\n")
    }
}

pub enum Statement {
    Assignment {
        identifier: String,
        parameters: Vec<String>,
        expression: Expression,
    },
}
impl Statement {
    pub fn to_string(&self) -> String {
        match self {
            Statement::Assignment {
                identifier,
                parameters,
                expression,
            } => {
                let params = parameters.join(", ");
                format!("{}({}) := {}", identifier, params, expression.to_string())
            }
        }
    }
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
        identifier: String,
        arguments: Vec<Expression>,
    },
    Match {
        cases: Vec<Case>,
    },
}
impl Expression {
    pub fn to_string(&self) -> String {
        match self {
            Expression::Literal(l) => l.to_string(),
            Expression::Binary {
                left,
                operator,
                right,
            } => format!(
                "({} {} {})",
                left.to_string(),
                operator.to_string(),
                right.to_string()
            ),
            Expression::Unary { operator, operand } => {
                format!("({} {})", operator.to_string(), operand.to_string())
            }
            Expression::Call {
                identifier,
                arguments,
            } => {
                let args = arguments
                    .iter()
                    .map(|arg| arg.to_string())
                    .collect::<Vec<_>>()
                    .join(", ");
                format!("{}({})", identifier, args)
            }
            Expression::Match { cases } => {
                let cases_str = cases
                    .iter()
                    .map(|case| case.to_string())
                    .collect::<Vec<_>>()
                    .join(", ");
                format!("{{ {} }}", cases_str)
            }
        }
    }
}

pub enum Literal {
    Identifier(String),
    Integer(i64),
    FloatingPoint(f64),
    Boolean(bool),
    Nothing,
}
impl Literal {
    pub fn to_string(&self) -> String {
        match self {
            Literal::Identifier(s) => s.to_string(),
            Literal::Integer(i) => i.to_string(),
            Literal::FloatingPoint(f) => f.to_string(),
            Literal::Boolean(b) => b.to_string(),
            Literal::Nothing => "Nothing".to_string(),
        }
    }
}

pub struct Case {
    pub pattern: Vec<Literal>,
    pub expression: Expression,
}
impl Case {
    pub fn to_string(&self) -> String {
        let pattern = self
            .pattern
            .iter()
            .map(|lit| lit.to_string())
            .collect::<Vec<_>>()
            .join(", ");
        format!("{} => {}", pattern, self.expression.to_string())
    }
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
impl BinaryOperator {
    pub fn to_string(&self) -> String {
        match self {
            BinaryOperator::Plus => "+".to_string(),
            BinaryOperator::Minus => "-".to_string(),
            BinaryOperator::Asterisk => "*".to_string(),
            BinaryOperator::Slash => "/".to_string(),
            BinaryOperator::Percent => "%".to_string(),
            BinaryOperator::Caret => "^".to_string(),
            BinaryOperator::Equal => "=".to_string(),
            BinaryOperator::NotEqual => "!=".to_string(),
            BinaryOperator::LessThan => "<".to_string(),
            BinaryOperator::GreaterThan => ">".to_string(),
            BinaryOperator::LessThanEqual => "<=".to_string(),
            BinaryOperator::GreaterThanEqual => ">=".to_string(),
            BinaryOperator::And => "&".to_string(),
            BinaryOperator::Or => "|".to_string(),
            BinaryOperator::NotAnd => "!&".to_string(),
            BinaryOperator::NotOr => "!|".to_string(),
        }
    }
}

pub enum UnaryOperator {
    Minus,
    Not,
}
impl UnaryOperator {
    pub fn to_string(&self) -> String {
        match self {
            UnaryOperator::Minus => "-".to_string(),
            UnaryOperator::Not => "!".to_string(),
        }
    }
}
