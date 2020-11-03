#pragma once

#include <string>
#include <variant>
#include <vector>

namespace sandbox {

  namespace tools {

    class Calculator {
      class Tokenizer {
      public:
        struct Token {
          enum class Type { Const, Operator, Function, Delimiter, LeftPar, RightPar };
          Type type;
          std::variant<double, std::string_view> value;

          explicit Token(double const_val);
          explicit Token(std::string_view string_val);
        };

      private:
        std::vector<Token> tokens;
        std::vector<Token>::const_iterator pos;
        std::string expression;

      public:
        Tokenizer();
        explicit Tokenizer(std::string_view expression);

        void setExpression(std::string_view expression);

        const Token* next();

      private:
        void tokenize(std::string_view expression);
      };

      Tokenizer tokenizer;

    public:
      Calculator();

      double calculate(std::string_view expression);
    };

  }

}
