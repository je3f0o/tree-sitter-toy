/**
 * @file HTML grammar for tree-sitter
 * @author Max Brunsfeld
 * @license MIT
 */

/* globals grammar, repeat, choice*/

/* eslint-disable arrow-parens */
/* eslint-disable camelcase */
/* eslint-disable-next-line spaced-comment */
/// <reference types="tree-sitter-cli/dsl" />
// @ts-check

module.exports = grammar({
  name: 'jeefo_template',

  rules: {
    document: $ => repeat($._node),

    _node: $ => choice(
      $.element,
    ),

    element: $ => choice(
      $.element_name,
    ),

    element_name: () => /[^.,>+\^\[\]\(\)="'#{} \t\r\n]+/,
  }
});