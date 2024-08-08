use super::token::{Token, TokenType};
use std::cmp::PartialEq;

pub struct Lexer {
    pub tokens: Vec<Token>,
    source: String,
    index: usize,
    line: usize,
    column: usize,
}
impl PartialEq for TokenType {
    fn eq(&self, other: &Self) -> bool {
        match (self, other) {
            (TokenType::Integer, TokenType::Integer) => true,
            (TokenType::FloatingPoint, TokenType::FloatingPoint) => true,
            (TokenType::Boolean, TokenType::Boolean) => true,
            (TokenType::Nothing, TokenType::Nothing) => true,
            (TokenType::Identifier, TokenType::Identifier) => true,
            (TokenType::Plus, TokenType::Plus) => true,
            (TokenType::Minus, TokenType::Minus) => true,
            (TokenType::Asterisk, TokenType::Asterisk) => true,
            (TokenType::Slash, TokenType::Slash) => true,
            (TokenType::Percent, TokenType::Percent) => true,
            (TokenType::Caret, TokenType::Caret) => true,
            (TokenType::Equal, TokenType::Equal) => true,
            (TokenType::Assign, TokenType::Assign) => true,
            (TokenType::NotEqual, TokenType::NotEqual) => true,
            (TokenType::LessThan, TokenType::LessThan) => true,
            (TokenType::GreaterThan, TokenType::GreaterThan) => true,
            (TokenType::LessThanEqual, TokenType::LessThanEqual) => true,
            (TokenType::GreaterThanEqual, TokenType::GreaterThanEqual) => true,
            (TokenType::Not, TokenType::Not) => true,
            (TokenType::And, TokenType::And) => true,
            (TokenType::Or, TokenType::Or) => true,
            (TokenType::NotAnd, TokenType::NotAnd) => true,
            (TokenType::NotOr, TokenType::NotOr) => true,
            (TokenType::Implies, TokenType::Implies) => true,
            (TokenType::Maplet, TokenType::Maplet) => true,
            (TokenType::LeftParenthesis, TokenType::LeftParenthesis) => true,
            (TokenType::RightParenthesis, TokenType::RightParenthesis) => true,
            (TokenType::LeftBracket, TokenType::LeftBracket) => true,
            (TokenType::RightBracket, TokenType::RightBracket) => true,
            (TokenType::LeftBrace, TokenType::LeftBrace) => true,
            (TokenType::RightBrace, TokenType::RightBrace) => true,
            (TokenType::Colon, TokenType::Colon) => true,
            (TokenType::Comma, TokenType::Comma) => true,
            (TokenType::Ellipsis, TokenType::Ellipsis) => true,
            (TokenType::LineFeed, TokenType::LineFeed) => true,
            (TokenType::Illegal, TokenType::Illegal) => true,
            (TokenType::EOF, TokenType::EOF) => true,
            _ => false,
        }
    }
}
impl Lexer {
    pub fn new(source: String) -> Lexer {
        Lexer {
            tokens: Vec::new(),
            source,
            index: 0,
            line: 1,
            column: 0,
        }
    }

    pub fn scan(&mut self) {
        while self.peek(0) != '\0' {
            self.ignore_whitespace();
            let c = self.consume();

            if c == '\n' {
                self.push(TokenType::LineFeed, ' '.to_string());
                self.line += 1;
                self.column = 0;
                continue;
            }

            if c.is_alphabetic() || c == '_' {
                let mut lexeme = c.to_string();
                while self.peek(0).is_digit(10)
                    || self.peek(0).is_alphanumeric()
                    || self.peek(0) == '_'
                {
                    lexeme.push(self.consume());
                }
                match lexeme.as_str() {
                    "Infinity" => self.push(TokenType::FloatingPoint, lexeme),
                    "Nan" => self.push(TokenType::FloatingPoint, lexeme),
                    "True" => self.push(TokenType::Boolean, lexeme),
                    "False" => self.push(TokenType::Boolean, lexeme),
                    "Nothing" => self.push(TokenType::Nothing, lexeme),
                    _ => self.push(TokenType::Identifier, lexeme),
                }
                continue;
            }

            if c.is_digit(10) {
                let mut lexeme = c.to_string();
                let mut is_float = false;
                let mut is_illegal = false;
                while self.peek(0).is_digit(10) || self.peek(0) == '.' {
                    lexeme.push(self.consume());
                    if self.peek(0) == '.' {
                        if is_float {
                            self.push(TokenType::Illegal, lexeme.clone());
                            is_illegal = true;
                            break;
                        }
                        is_float = true;
                    }
                }
                if is_illegal {
                    continue;
                }
                if is_float {
                    self.push(TokenType::FloatingPoint, lexeme);
                } else {
                    self.push(TokenType::Integer, lexeme);
                }
                continue;
            }

            match c {
                '+' => self.push(TokenType::Plus, c.to_string()),
                '-' => match self.peek(0) {
                    '>' => {
                        self.consume();
                        self.push(TokenType::Maplet, "->".to_string());
                    }
                    _ => self.push(TokenType::Minus, c.to_string()),
                },
                '*' => self.push(TokenType::Asterisk, c.to_string()),
                '/' => match self.peek(0) {
                    '/' => {
                        while self.peek(0) != '\n' && self.peek(0) != '\0' {
                            self.consume();
                        }
                    }
                    _ => self.push(TokenType::Slash, c.to_string()),
                },
                '%' => self.push(TokenType::Percent, c.to_string()),
                '^' => self.push(TokenType::Caret, c.to_string()),
                '=' => match self.peek(0) {
                    '>' => {
                        self.consume();
                        self.push(TokenType::Implies, "=>".to_string());
                    }
                    _ => self.push(TokenType::Equal, c.to_string()),
                },
                ':' => match self.peek(0) {
                    '=' => {
                        self.consume();
                        self.push(TokenType::Assign, ":=".to_string());
                    }
                    _ => self.push(TokenType::Colon, c.to_string()),
                },
                '!' => match self.peek(0) {
                    '=' => {
                        self.consume();
                        self.push(TokenType::NotEqual, "!=".to_string());
                    }
                    '&' => {
                        self.consume();
                        self.push(TokenType::NotAnd, "!&".to_string());
                    }
                    '|' => {
                        self.consume();
                        self.push(TokenType::NotOr, "!|".to_string());
                    }
                    _ => self.push(TokenType::Not, c.to_string()),
                },
                '<' => match self.peek(0) {
                    '=' => {
                        self.consume();
                        self.push(TokenType::LessThanEqual, "<=".to_string());
                    }
                    _ => self.push(TokenType::LessThan, c.to_string()),
                },
                '>' => match self.peek(0) {
                    '=' => {
                        self.consume();
                        self.push(TokenType::GreaterThanEqual, ">=".to_string());
                    }
                    _ => self.push(TokenType::GreaterThan, c.to_string()),
                },
                '&' => self.push(TokenType::And, c.to_string()),
                '|' => self.push(TokenType::Or, c.to_string()),
                '(' => self.push(TokenType::LeftParenthesis, c.to_string()),
                ')' => self.push(TokenType::RightParenthesis, c.to_string()),
                '[' => self.push(TokenType::LeftBracket, c.to_string()),
                ']' => self.push(TokenType::RightBracket, c.to_string()),
                '{' => self.push(TokenType::LeftBrace, c.to_string()),
                '}' => self.push(TokenType::RightBrace, c.to_string()),
                ',' => self.push(TokenType::Comma, c.to_string()),
                '.' => {
                    if self.peek(0) == '.' && self.peek(1) == '.' {
                        self.consume();
                        self.consume();
                        self.push(TokenType::Ellipsis, c.to_string());
                    } else {
                        self.push(TokenType::Illegal, c.to_string());
                    }
                }
                _ => self.push(TokenType::Illegal, c.to_string()),
            }
        }
        self.push(TokenType::EOF, "".to_string());
        self.post_process();
    }

    fn push(&mut self, token_type: TokenType, lexeme: String) {
        let column = self.column - lexeme.len() + 1;
        self.tokens
            .push(Token::new(token_type, lexeme, self.line, column));
    }

    fn post_process(&mut self) {
        let mut i = 0;
        while i < self.tokens.len() - 1 {
            if self.tokens[i].token_type == TokenType::Illegal {
                panic!( // TODO: make clickable
                    "Illegal token '{}' at {}:{}",
                    self.tokens[i].lexeme, self.tokens[i].line, self.tokens[i].column
                );
            }
            i += 1;
        }

        if self.tokens[self.tokens.len() - 2].token_type != TokenType::LineFeed {
            self.tokens.pop();
            self.column += 1;
            self.push(TokenType::LineFeed, " ".to_string());
            self.line += 1;
            self.column = 0;
            self.push(TokenType::EOF, "".to_string());
        }

        let mut i = 0;
        while i < self.tokens.len() - 1 {
            if self.tokens[i].token_type == TokenType::LineFeed
                && self.tokens[i + 1].token_type == TokenType::LineFeed
            {
                self.tokens.remove(i + 1);
            } else {
                i += 1;
            }
        }

        if self.tokens[0].token_type == TokenType::LineFeed {
            self.tokens.remove(0);
        }

        let mut i = 0;
        while i < self.tokens.len() - 1 {
            match self.tokens[i].token_type {
                TokenType::LeftParenthesis
                | TokenType::LeftBracket
                | TokenType::LeftBrace
                | TokenType::Comma => {
                    if self.tokens[i + 1].token_type == TokenType::LineFeed {
                        self.tokens.remove(i + 1);
                    }
                }
                _ => {},
            }
            i += 1;
        }

        let mut i = 0;
        while i < self.tokens.len() - 1 {
            if self.tokens[i].token_type == TokenType::Comma {
                match self.tokens[i + 1].token_type {
                    TokenType::RightParenthesis
                    | TokenType::RightBracket
                    | TokenType::RightBrace => {
                        self.tokens.remove(i);
                    }
                    _ => {},
                }
            }
            i += 1;
        }
    }

    fn peek(&self, offset: usize) -> char {
        self.source.chars().nth(self.index + offset).unwrap_or('\0')
    }

    fn consume(&mut self) -> char {
        let c = self.peek(0);
        self.index += 1;
        self.column += 1;
        c
    }

    fn ignore_whitespace(&mut self) {
        while self.peek(0).is_whitespace() && self.peek(0) != '\n' {
            self.consume();
        }
    }
}
