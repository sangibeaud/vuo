Routes the selected input port's list to the output port.

This node is useful for choosing between different data. The `Option` inputs can come from different data sources, and the `Which` input port can pick one of them to use.

The `Which` port selects the `Option` input port that will be routed to the output port. If `Which` is <i>false</i>, it selects `False Option`. If `Which` is <i>true</i>, it selects `True Option`.

Events that come in through the currently selected `Option` port are passed on through the output port. Events that come in through the other `Option` port are blocked.

This node's `Which` port lets you select between options using a boolean (true/false) value. If instead you want to select between two options using an integer (numerical) value, you can use a [Select Input List (2)](vuo-node://vuo.select.in.list.2) or [Select Input List (8)](vuo-node://vuo.select.in.list.8) node.
