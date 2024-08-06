pub enum TokenType {
    Identifier,    // /\w+/
    Integer,       // /([+-]?\d+)/
    FloatingPoint, // /([+-]?\d+\.\d+|Infinity|NaN)/
    Boolean,       // /(True|False)/
    Nothing,       // /Nothing/

    Plus,     // +
    Minus,    // -
    Asterisk, // *
    Slash,    // /
    Percent,  // %
    Caret,    // ^

    Equal,    // =
    Assign,   // :=
    NotEqual, // !=

    LessThan,         // <
    GreaterThan,      // >
    LessThanEqual,    // <=
    GreaterThanEqual, // >=

    Not,    // !
    And,    // &
    Or,     // |
    NotAnd, // !&
    NotOr,  // !|

    Implies, // =>

    Maplet, // ->

    LeftParenthesis,  // (
    RightParenthesis, // )
    LeftBracket,      // [
    RightBracket,     // ]
    LeftBrace,        // {
    RightBrace,       // }

    Colon,    // :
    Comma,    // ,
    Ellipsis, // ...

    Illegal,
    EOF,
}

impl TokenType {
    pub fn to_string(&self) -> String {
        match self {
            TokenType::Identifier => "Identifier",
            TokenType::Integer => "Integer",
            TokenType::FloatingPoint => "FloatingPoint",
            TokenType::Boolean => "Boolean",
            TokenType::Nothing => "Nothing",
            TokenType::Plus => "Plus",
            TokenType::Minus => "Minus",
            TokenType::Asterisk => "Asterisk",
            TokenType::Slash => "Slash",
            TokenType::Percent => "Percent",
            TokenType::Caret => "Caret",
            TokenType::Equal => "Equal",
            TokenType::Assign => "Assign",
            TokenType::NotEqual => "NotEqual",
            TokenType::LessThan => "LessThan",
            TokenType::GreaterThan => "GreaterThan",
            TokenType::LessThanEqual => "LessThanEqual",
            TokenType::GreaterThanEqual => "GreaterThanEqual",
            TokenType::Not => "Not",
            TokenType::And => "And",
            TokenType::Or => "Or",
            TokenType::NotAnd => "NotAnd",
            TokenType::NotOr => "NotOr",
            TokenType::Implies => "Implies",
            TokenType::Maplet => "Maplet",
            TokenType::LeftParenthesis => "LeftParenthesis",
            TokenType::RightParenthesis => "RightParenthesis",
            TokenType::LeftBracket => "LeftBracket",
            TokenType::RightBracket => "RightBracket",
            TokenType::LeftBrace => "LeftBrace",
            TokenType::RightBrace => "RightBrace",
            TokenType::Colon => "Colon",
            TokenType::Comma => "Comma",
            TokenType::Ellipsis => "Ellipsis",
            TokenType::Illegal => "Illegal",
            TokenType::EOF => "EOF",
        }
        .to_string()
    }
}

pub struct Token {
    token_type: TokenType,
    lexeme: String,
    line: usize,
    column: usize,
}

impl Token {
    pub fn new(token_type: TokenType, lexeme: String, line: usize, column: usize) -> Token {
        Token {
            token_type,
            lexeme,
            line,
            column,
        }
    }

    pub fn to_string(&self) -> String {
        format!(
            "{:>4}:{:<5}{:<17}{}",
            self.line,
            self.column - self.lexeme.len() + 1,
            self.token_type.to_string(),
            self.lexeme,
        )
    }
}
