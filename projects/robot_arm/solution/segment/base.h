#pragma once

#include <string>
#include <memory>

#include "point.h"
#include "debug.h"

namespace Segment {

  class Base {
    public:
      Base (const std::string& type) :
        m_next (nullptr),
        m_type (type) {
          debug::log ("constructing segment of type " + m_type);
        }
      Base (const Base& other) = delete;
      Base& operator= (const Base& other) = delete;

      virtual ~Base();

      Base& set_next (std::shared_ptr<Base> next) {
        m_next = next;
        return *m_next;
      }

      const std::string& type () const { return m_type; }
      virtual Point tip_position () const = 0;
      virtual void set_angle (int n, double angle);

    protected:
      std::shared_ptr<Base> m_next;
      const std::string m_type;
  };

}
