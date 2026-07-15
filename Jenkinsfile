pipeline {
    agent {
        label 'cpp-agent'
    }

    stages {
        stage('Pull') {
            steps {
                checkout scm
            }
        }

        stage('Build C++') {
            steps {
                sh '''
                    set -e

                    mkdir -p build

                    g++ -std=c++20 \
                        src/*.cpp \
                        -Iinclude \
                        -o build/myapp
                '''
            }
        }

        stage('Save Artifact') {
            steps {
                archiveArtifacts(
                    artifacts: 'build/myapp',
                    fingerprint: true
                )
            }
        }

    }
}
