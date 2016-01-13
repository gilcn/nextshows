# Reporting an issue with nextShows #

If you experience problems like crashes or malfunctions please follow the following steps before filling your report, this will make finding the origin of the problem easier.

  1. Make sure you activate the debug feature:
    * edit `~/.superkaramba/nextShows/nextShows.conf` and under the `[main]` section set:
      * `debug = True`
  1. From a TERMinal launch nextShows by typing:
    * `$ superkaramba nextShows-x.y.z.skz`  _(obviously, replace x.y.z with the correct version number)_
  1. Spot the parts of the debug messages that gives hints about the problem
  1. Paste this inside your [bug report](http://code.google.com/p/nextshows/issues/list)