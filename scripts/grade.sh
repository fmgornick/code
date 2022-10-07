#!/bin/sh
LIB_PATH=$1

if ! test -f "$LIB_PATH/routing/src/graph.cc"
  then
    echo "graph.cc DOES NOT EXIST"
    exit 1
  else
    printf "number of lines in graph.cc: "
    wc -l "$LIB_PATH/routing/src/graph.cc"
fi
if ! test -f "$LIB_PATH/routing/src/parsers/osm/osm_parser.cc"
  then
    echo "osm_parser.cc DOES NOT EXIST"
    exit 1
  else
    printf "number of lines in osm_parser.cc: "
    wc -l "$LIB_PATH/routing/src/parsers/osm/osm_parser.cc"
fi
if ! test -f "$LIB_PATH/routing/src/routing/pathing.cc"
  then
    echo "pathing.cc DOES NOT EXIST"
    exit 1
  else
    printf "number of lines in pathing.cc: "
    wc -l "$LIB_PATH/routing/src/routing/pathing.cc"
fi

GRAPH_ERRORS=$(
  cpplint \
  --filter=-legal/copyright,-build/include,-build/namespaces,-runtime/explicit \
  2>&1 \
  "$LIB_PATH"/routing/src/graph.cc | awk '$0 ~ /^Total errors found/ {print $NF}'
)
GRAPH_ERRORS=$((GRAPH_ERRORS + 0))

PARSER_ERRORS=$(
  cpplint \
  --filter=-legal/copyright,-build/include,-build/namespaces,-runtime/explicit \
  2>&1 \
  "$LIB_PATH"/routing/src/parsers/osm/osm_parser.cc | awk '$0 ~ /^Total errors found/ {print $NF}'
)
PARSER_ERRORS=$((PARSER_ERRORS + 0))

PATHING_ERRORS=$(
  cpplint \
  --filter=-legal/copyright,-build/include,-build/namespaces,-runtime/explicit \
  2>&1 \
  "$LIB_PATH"/routing/src/routing/pathing.cc | awk '$0 ~ /^Total errors found/ {print $NF}'
)
PATHING_ERRORS=$((PATHING_ERRORS + 0))

printf "graph.cc errors      : %s\n" "$GRAPH_ERRORS"
printf "osm_parser.cc errors : %s\n" "$PARSER_ERRORS"
printf "pathing.cc errors    : %s\n" "$PATHING_ERRORS"
printf "TOTAL ERRORS         : %d\n" $((GRAPH_ERRORS + PARSER_ERRORS + PATHING_ERRORS))
