//
// Created by BEN on 2/8/24.
//

#ifndef token_type_hpp
#define token_type_hpp

enum TokenType {
    // Tokens       // Regular expressions:
    tok_na,         // n/a
    tok_eof,        // EOF
    tok_bit,        // './'
    tok_clone,      // ',/'
    tok_dub,        // '!'
    tok_pop,        // '?'
    tok_mul,        // '*'
    tok_div,        // '/'
    tok_plus,       // '+'
    tok_minus,      // '-'
    tok_string,     // '%'
    tok_rhead,      // '@<'
    tok_lhead,      // '>@'
    tok_ehead,      // '@='
    tok_body,       // '###'
    tok_duck_fr,    // '  @<'
                    // '###'
    tok_duck_fl,    // '>@'
                    // ' ###'
    tok_duck_er,    // '  @='
                    // '###'
    tok_leg,        // ','
    tok_arrow,      // '->'
    tok_keyword,
    tok_id
};

#endif // token_type_hpp
