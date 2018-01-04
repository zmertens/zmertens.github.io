#!/usr/bin/python
import mistune as mt

""" My website, where I attempt to decrypt my consciousnes
    I use mistune to turn the Markdown-formatted strings
    into html. That's it.
"""

__author__ = 'zmertens'
__version__ = 0.1

indexStr = """
# zmertens.github.io
 - [About](About/about.html)
 - [Poems](Poems/poems.html)
"""

aboutStr = """
# GitHub user: @zmertens
 - Aspiring programmer and freelancer
 - Loves dogs
 - Enjoys discovering new music on Spotify and elsewhere
 - Motorcycles are cool
 - Recently discovered how cool Cython can be for bridging C++ and Python
 - [Fire](Images/green_fire.jpg)
 - Stays up late writing, musing

> If you can't write good code, try to write good comments
> Else if you can't write good comments, try to listen
> Else, teach Jim
"""

poemsStr = """
# Envy
Treants set on Fire
Racing like loops until harvest
Harvest the Envy
Earthen Throne
Everybody's home
Reminder of integrity
Stolen idolatry
Treants from the Forest for the Trees
Burning the leaves
The leaves that fall, like seasons, like relationships
Running through fire, the transformation
Timeline that stretches, proving desperation
Treants like our friends
Forest keepers, guarding the Den
Chaotic destruction
Ignoring the warnings, blazing, ashes
Coveting the Throne, stolen Home
Now I wander alone, looking for calm
Remedy from the flame
To seek a home again, to emblazen my name

# Burnout
Randomized Nouns
Triangulation, verbatim
Buying, selling, trading, bowing, heading
Broken glasses, distorted views
Immeasurable faces, haunting &self
Hunting for memories
Aliteral translation
Complexity is easy
Confused by the mass
Perplexed by the speech
Elders imcomprehensible
Listeners that can't be watchers
Forests of azure
Suffucating wheels spinning
Collapsing sun, Jupiter's horizon
Mother Nature's wisdom
Smoke scattering, wheels blurring
Engines revving, whistles turning
Knees dragging, elbows flailing
Rapidly unioninzing engines ; Machine Nation
Burning and fleeing free from the clutch
Paradise forgotten
Oil drenched cement gasoline
So what if I made a big mistake?
Shifting lateralusly and fishboning
The Burnout filters the remainders
All those who will be wasted
"""

def writeHtmlFromMarkdown(markdownDevice, markdownStr, fileName):
    htmlStr = markdownDevice(markdownStr)
    fileOut = open(fileName, "w")
    fileOut.write(htmlStr)
    fileOut.close()

renderer = mt.Renderer(escape=True, hard_wrap=True)
markdown = mt.Markdown(renderer=renderer)
writeHtmlFromMarkdown(markdown, indexStr, "index.html")
writeHtmlFromMarkdown(markdown, aboutStr, "About/about.html")
writeHtmlFromMarkdown(markdown, poemsStr, "Poems/poems.html")
# indexHtml = markdown(indexStr)
# indexHtmlOut = open("Index.html", "w")
# indexHtmlOut.write(indexHtml)
# indexHtmlOut.close()
