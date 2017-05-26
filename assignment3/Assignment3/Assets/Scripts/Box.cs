using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class Box : MonoBehaviour {
 
    public void explode()
    {
        Destroy(gameObject,1.0f);
        Mesh mesh = this.GetComponent<MeshFilter>().mesh;
        mesh.Clear();
        this.GetComponent<ParticleSystem>().Play();
        
    }
}
