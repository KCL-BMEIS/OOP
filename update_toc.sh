#!/bin/bash

url="https://kcl-bmeis.github.io/OOP"

echo ---
echo "layout: default"
echo "title: links to topics in slides - Object-Oriented Programming (5CCYB041)"

for f in week*.md; do 
  echo ---
  echo ""
  echo -n "#" 

  get_name=0
  while read line; do 
    if [[ "$line" =~ ^title: ]]; then 
      line="${line#*:}"
      echo "# ${line/\"/}"
      echo ""
      continue
    fi

    if [[ "$line" =~ ^name: ]]; then
      get_name=1
      ref=${line#*:}
      ref=${ref/ /}
      continue
    fi

    [[ -z "$ref" ]] && continue

    if [[ "$line" =~ ^\#\  ]]; then
      name=${line#\# }
      echo "- [$name]($url/${f%.md}.html#$ref)"
      unset ref
    fi

  done < $f

  echo ""
done
