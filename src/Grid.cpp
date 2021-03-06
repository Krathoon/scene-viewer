#include "Grid.h"

Grid::Grid( unsigned int lineCount ) {
    // There needs to be an odd number of lines
    lineCount |= 1;
    const unsigned int pointCount = lineCount * 4;
    const unsigned int verticesSize = pointCount * ( 3 + 3 );  // (3 (position(xyz) + 3 color(rgb))

    std::vector<float> vertices;
    vertices.resize( verticesSize );

    const float gridLength = (float)( lineCount / 2 );
    float value = -gridLength;
    for ( unsigned int i = 0; i < verticesSize; ++i ) {
        // Default line color is dark grey
        Vector4 color( 0.3f, 0.3f, 0.3f, 1.0f );

        // Very 10th line is brighter grey
        if ( ( (int)value ) % 10 == 0 ) {
            color.set( 0.45f, 0.45f, 0.45f, 1.0f );
        }

        // The Z axis is blue
        if ( value == 0.0f ) {
            color.set( 0.15f, 0.15f, 0.7f, 1.0f );
        }

        // Build the lines
        vertices[i] = value;
        vertices[++i] = 0.0f;
        vertices[++i] = -gridLength;
        vertices[++i] = color.x;
        vertices[++i] = color.y;
        vertices[++i] = color.z;

        vertices[++i] = value;
        vertices[++i] = 0.0f;
        vertices[++i] = gridLength;
        vertices[++i] = color.x;
        vertices[++i] = color.y;
        vertices[++i] = color.z;

        // The X axis is red
        if ( value == 0.0f ) {
            color.set( 0.7f, 0.15f, 0.15f, 1.0f );
        }
        vertices[++i] = -gridLength;
        vertices[++i] = 0.0f;
        vertices[++i] = value;
        vertices[++i] = color.x;
        vertices[++i] = color.y;
        vertices[++i] = color.z;

        vertices[++i] = gridLength;
        vertices[++i] = 0.0f;
        vertices[++i] = value;
        vertices[++i] = color.x;
        vertices[++i] = color.y;
        vertices[++i] = color.z;

        value += 1.0f;
    }
    VertexFormat::Element elements[] = {VertexFormat::Element( VertexFormat::POSITION, 3 ),
                                        VertexFormat::Element( VertexFormat::COLOR, 3 )};
    Mesh* mesh = Mesh::createMesh( VertexFormat( elements, 2 ), pointCount, false );
    mesh->setPrimitiveType( Mesh::LINES );
    mesh->setVertexData( &vertices[0], 0, pointCount );

    Model* model = Model::create( mesh );
    model->setMaterial( "res/scene_viewer.material#grid" );
    SAFE_RELEASE( mesh );
    _node = Node::create("grid");
    _node->setModel( model );
    model->release();
}

Grid* Grid::create( unsigned int lineCount ) { 
    return new Grid( lineCount ); 
}

void Grid::draw() { 
    _node->getModel()->draw(); 
}
