mod storr;

use crate::storr::lexer::Lexer;
use std::env;
use std::fs;

#[macro_export]
macro_rules! run {
    ($source:expr) => {{
        let mut lexer = Lexer::new($source.to_string());
        lexer.scan();
        let tokens = lexer.tokens;
        for token in &tokens {
            println!("{}", token.to_string());
        }

    }};
}

fn main() {
    let args: Vec<String> = env::args().collect();

    if args.len() != 2 {
        println!("Usage: storr <filename>");
        return;
    }

    let path = &args[1];
    match fs::read_to_string(path) {
        Err(e) => println!("Error: {}", e),
        Ok(source) => run!(&source),
    }
}
