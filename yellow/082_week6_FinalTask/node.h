/*
 * node.h
 *
 *  Created on: Dec 18, 2018
 *      Author: Anton Dogadaev
 */

#pragma once

#include <string>
#include <memory>

#include "date.h"

using namespace std;

enum class Comparison {
    Less,
    LessOrEqual,
    Greater,
    GreaterOrEqual,
    Equal,
    NotEqual,
};

enum class LogicalOperation {
    Or,
    And,
};

class Node {
public:
    virtual bool Evaluate(Date d, string event) const = 0;
};

class EmptyNode : public Node {
public:
    bool Evaluate(Date d, string event) const override { return true; }
};

class DateComparisonNode : public Node {
public:
    DateComparisonNode(Comparison cmp, Date d) : cmp_(cmp), d_(d) {}

    bool Evaluate(Date d, string event) const override {
        if (cmp_ == Comparison::Less) {
            return d < d_;
        } else if (cmp_ == Comparison::LessOrEqual) {
            return d <= d_;
        } else if (cmp_ == Comparison::Equal) {
            return d == d_;
        } else if (cmp_ == Comparison::NotEqual) {
            return d != d_;
        } else if (cmp_ == Comparison::GreaterOrEqual) {
            return d >= d_;
        } else if (cmp_ == Comparison::Greater) {
            return d > d_;
        }
        throw logic_error("Unknown comparison value in DateComparisonNode: " +
                          to_string((int)cmp_));
    }
private:
    Comparison cmp_;
    Date d_;
};

class EventComparisonNode : public Node {
public:
    EventComparisonNode(Comparison cmp, string event) :
            cmp_(cmp), event_(event) {}

    bool Evaluate(Date d, string event) const override {
        if (cmp_ == Comparison::Less) {
            return event < event_;
        } else if (cmp_ == Comparison::LessOrEqual) {
            return event <= event_;
        } else if (cmp_ == Comparison::Equal) {
            return event == event_;
        } else if (cmp_ == Comparison::NotEqual) {
            return event != event_;
        } else if (cmp_ == Comparison::GreaterOrEqual) {
            return event >= event_;
        } else if (cmp_ == Comparison::Greater) {
            return event > event_;
        }
        throw logic_error("Unknown comparison value in EventComparisonNode: " +
                          to_string((int)cmp_));
    }
private:
    Comparison cmp_;
    string event_;
};

class LogicalOperationNode : public Node {
public:
    LogicalOperationNode(LogicalOperation lo, shared_ptr<Node> left,
                         shared_ptr<Node> right) : lo_(lo), left_(left),
                                                   right_(right) {}

    bool Evaluate(Date d, string event) const override {
        if (lo_ == LogicalOperation::And) {
            return (left_->Evaluate(d, event) && right_->Evaluate(d, event));
        } else if (lo_ == LogicalOperation::Or) {
            return (left_->Evaluate(d, event) || right_->Evaluate(d, event));
        }
        throw logic_error("Unknown logical operation in LogicalOperationNode");
    }
private:
    LogicalOperation lo_;
    shared_ptr<Node> left_;
    shared_ptr<Node> right_;
};
