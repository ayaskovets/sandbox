#include "calculator.hpp"

#include <algorithm>
#include <stack>
#include <unordered_map>
#include <functional>
#include <optional>
#include <tuple>
#include <cmath>

namespace sandbox {

  namespace tools {

    template<typename T>
    T popReturn(std::stack<T>& stack) {
      T result = stack.top();
      stack.pop();
      return result;
    }

    namespace calculator {
      // constants
      static const std::unordered_map< std::string_view, double > supported_constants = {
          std::make_pair("e", 2.71828182845904523536),
          std::make_pair("pi", 3.14159265358979323846),
      };

      double add(std::stack<double>& args) {
        return sandbox::tools::popReturn(args) + sandbox::tools::popReturn(args);
      }
      double sub(std::stack<double>& args) {
        double subtrahend = sandbox::tools::popReturn(args);
        double minuend = sandbox::tools::popReturn(args);
        return minuend - subtrahend;
      }
      double mul(std::stack<double>& args) {
        return sandbox::tools::popReturn(args) * sandbox::tools::popReturn(args);
      }
      double div(std::stack<double>& args) {
        double divisor = sandbox::tools::popReturn(args);
        double dividend = sandbox::tools::popReturn(args);
        return dividend / divisor;
      }
      double pow(std::stack<double>& args) {
        double exp = sandbox::tools::popReturn(args);
        double base = sandbox::tools::popReturn(args);
        return std::pow(base, exp);
      }
      // operators with corresponding proprity (bigger numbers are prioritized) and associativity : true = left, false = right
      static const std::unordered_map< std::string_view, std::tuple< size_t, bool, std::function<double(std::stack<double>&)> > > supported_operators = {
          std::make_pair("^", std::make_tuple(3, false, std::bind(std::ref(pow), std::placeholders::_1))),
          std::make_pair("*", std::make_tuple(2, true, std::bind(std::ref(mul), std::placeholders::_1))),
          std::make_pair("/", std::make_tuple(2, true, std::bind(std::ref(div), std::placeholders::_1))),
          std::make_pair("+", std::make_tuple(1, true, std::bind(std::ref(add), std::placeholders::_1))),
          std::make_pair("-", std::make_tuple(1, true, std::bind(std::ref(sub), std::placeholders::_1)))
      };

      // functions
      double sin(std::stack<double>& args) {
        return std::sin(sandbox::tools::popReturn(args));
      }
      double cos(std::stack<double>& args) {
        return std::cos(sandbox::tools::popReturn(args));
      }
      static const std::unordered_map< std::string_view, std::function<double(std::stack<double>&)> > supported_functions = {
          std::make_pair("sin", std::bind(std::ref(sin), std::placeholders::_1)),
          std::make_pair("cos", std::bind(std::ref(cos), std::placeholders::_1))
      };

    }

    // Token
    Calculator::Tokenizer::Token::Token(double const_val) : type(Type::Const), value(const_val) {}
    Calculator::Tokenizer::Token::Token(std::string_view string_val) : value(string_val) {
      if (!string_val.compare(",")) {
        type = Type::Delimiter;
      }
      else if (!string_val.compare("(")) {
        type = Type::LeftPar;
      }
      else if (!string_val.compare(")")) {
        type = Type::RightPar;
      }
      else if (calculator::supported_operators.find(string_val) != calculator::supported_operators.end()) {
        type = Type::Operator;
      }
      else if (calculator::supported_functions.find(string_val) != calculator::supported_functions.end()) {
        type = Type::Function;
      }
      else {
        throw std::logic_error(std::string("Unknown token: ").append(string_val));
      }
    };

    // Tokenizer
    //** Tokenizer helper functions //
    std::optional<double> read_number(std::string_view::const_iterator& expr_it, std::string_view::const_iterator expr_end) {
      std::optional<double> number;

      if (isdigit(*expr_it)) {
        const char* number_begin = &*expr_it;
        char* number_end = const_cast<char*>(&*expr_it);

        number.emplace(std::strtod(number_begin, &number_end));
        std::advance(expr_it, number_end - number_begin);
      }
      else {
        std::optional<std::string_view> cnst_str;
        for (const auto& cnst : calculator::supported_constants) {
          if (cnst.first.size() < static_cast<size_t>(std::distance(expr_it, expr_end)) && !cnst.first.compare(0, cnst.first.size(), &*expr_it, cnst.first.size())) {
            if (!cnst_str.has_value() || cnst_str.value().size() < cnst.first.size()) {
              cnst_str.emplace(cnst.first);
              number.emplace(cnst.second);
            }
          }
        }

        if (cnst_str.has_value()) {
          std::advance(expr_it, cnst_str.value().size());
        }
      }

      return number;
    }
    std::optional<std::string_view> read_operator(std::string_view::const_iterator& expr_it, std::string_view::const_iterator expr_end) {
      std::optional<std::string_view> oper;

      for (const auto& op : calculator::supported_operators) {
        if (op.first.size() < static_cast<size_t>(std::distance(expr_it, expr_end)) && !op.first.compare(0, op.first.size(), &*expr_it, op.first.size())) {
          if (!oper.has_value() || oper.value().size() < op.first.size()) {
            oper.emplace(op.first);
          }
        }
      }

      if (oper.has_value()) {
        std::advance(expr_it, oper.value().size());
      }

      return oper;
    }
    std::optional<std::string_view> read_function(std::string_view::const_iterator& expr_it, std::string_view::const_iterator expr_end) {
      std::optional<std::string_view> function;

      for (const auto& fn : calculator::supported_functions) {
        if (fn.first.size() < static_cast<size_t>(std::distance(expr_it, expr_end)) && !fn.first.compare(0, fn.first.size(), &*expr_it, fn.first.size())) {
          if (!function.has_value() || function.value().size() < fn.first.size()) {
            function.emplace(fn.first);
          }
        }
      }

      if (function.has_value()) {
        std::advance(expr_it, function.value().size());
      }

      return function;
    }
    std::string prepare_expression(std::string&& expression) {
      expression.erase(std::remove(expression.begin(), expression.end(), ' '), expression.end());
      expression.erase(std::remove(expression.begin(), expression.end(), '\n'), expression.end());
      expression.erase(std::remove(expression.begin(), expression.end(), '\r'), expression.end());

      return std::move(expression);
    }
    // Tokenizer helper functions **//

    Calculator::Tokenizer::Tokenizer() {}
    Calculator::Tokenizer::Tokenizer(std::string_view expression) {
      setExpression(expression);
    }

    void Calculator::Tokenizer::setExpression(std::string_view expression) {
      tokens.clear();
      tokenize(expression = std::move(prepare_expression(std::string(expression))));
      pos = tokens.cbegin();
    }

    const Calculator::Tokenizer::Token* Calculator::Tokenizer::next() {
      if (pos != tokens.cend()) {
        return &*pos++;
      }
      else {
        return nullptr;
      }
    };

    void Calculator::Tokenizer::tokenize(std::string_view expression) {
      for (auto expr_it = expression.cbegin(); expr_it < expression.cend(); std::advance(expr_it, 1)) {
        const auto function = read_function(expr_it, expression.cend());
        if (function.has_value()) {
          tokens.emplace_back(Token(function.value()));
          std::advance(expr_it, -1);
          continue;
        }

        const auto number = read_number(expr_it, expression.cend());
        if (number.has_value()) {
          tokens.emplace_back(Token(number.value()));
          std::advance(expr_it, -1);
          continue;
        }

        const auto oper = read_operator(expr_it, expression.cend());
        if (oper.has_value()) {
          tokens.emplace_back(Token(oper.value()));
          std::advance(expr_it, -1);
          continue;
        }

        tokens.emplace_back(Token(std::string_view(&*expr_it, 1)));
      }
    };

    // Calculator
    Calculator::Calculator() {}

    double Calculator::calculate(std::string_view expression) {
      typedef Calculator::Tokenizer::Token::Type TokenType;

      std::stack<double> result;
      if (!expression.empty()) {
        tokenizer.setExpression(std::string(expression));

        std::stack<const Calculator::Tokenizer::Token*> shunting_stack;

        auto addToken = [&](const Calculator::Tokenizer::Token* token) {
          if (token->type == TokenType::Const) {
            result.push(std::get<double>(token->value));
          }
          else if (token->type == TokenType::Operator) {
            result.push(std::get< std::function<double(std::stack<double>&)> >(calculator::supported_operators.find(std::get<std::string_view>(token->value))->second)(result));
          }
          else if (token->type == TokenType::Function) {
            result.push(calculator::supported_functions.find(std::get<std::string_view>(token->value))->second(result));
          }
        };

        // shunting yard
        while (const Calculator::Tokenizer::Token* token = tokenizer.next()) {
          switch (token->type) {
          case TokenType::Const:
            addToken(token);
            break;
          case TokenType::LeftPar:
          case TokenType::Function:
            shunting_stack.push(token);
            break;
          case TokenType::Operator:
            if (shunting_stack.empty() || shunting_stack.top()->type == TokenType::LeftPar) {
              shunting_stack.push(token);
            }
            else {
              const auto token_op = calculator::supported_operators.find(std::get<std::string_view>(token->value))->second;
              while (!shunting_stack.empty()) {
                if (shunting_stack.top()->type == TokenType::Operator) {
                  const auto top_stack_op = calculator::supported_operators.find(std::get<std::string_view>(shunting_stack.top()->value))->second;

                  if (std::get<bool>(token_op)) {
                    if (std::get<size_t>(token_op) <= std::get<size_t>(top_stack_op)) {
                      addToken(sandbox::tools::popReturn(shunting_stack));
                      continue;
                    }
                  }
                  else if (std::get<size_t>(token_op) < std::get<size_t>(top_stack_op)) {
                    addToken(sandbox::tools::popReturn(shunting_stack));
                    continue;
                  }
                }
                // assume that function priority is always bigger than any operator
                else if (shunting_stack.top()->type == TokenType::Function) {
                  addToken(sandbox::tools::popReturn(shunting_stack));
                  continue;
                }

                break;
              }

              shunting_stack.push(token);
            }
            break;
          case TokenType::RightPar:
            while (!shunting_stack.empty() && shunting_stack.top()->type != TokenType::LeftPar) {
              addToken(sandbox::tools::popReturn(shunting_stack));
            }

            if (shunting_stack.top()->type != TokenType::LeftPar) {
              throw std::logic_error("Brackets mismatch");
            }

            shunting_stack.pop();

            if (shunting_stack.top()->type == TokenType::Function) {
              addToken(sandbox::tools::popReturn(shunting_stack));
            }

            break;
          case TokenType::Delimiter:
            break;
          }
        }

        while (!shunting_stack.empty()) {
          addToken(shunting_stack.top());
          shunting_stack.pop();
        }

        if (result.size() != 1) {
          throw std::logic_error("Calculation error");
        }

        return result.top();
      }

      return 0;
    }

  }

}
