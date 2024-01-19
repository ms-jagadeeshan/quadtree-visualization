Quadtree X OpenGL
=================

This is the OpenGL visualization of the quadtree.


.. image:: images/QuadTree.png


Build
-----

.. code-block:: bash
   git clone https://github.com/ms-jagadeeshan/quadtree-visualization.git
   g++ quad-x-gl.cpp quadtree.cpp -o quad-x-gl -lGL -lGLU -lglut
   ./quad-x-gl
