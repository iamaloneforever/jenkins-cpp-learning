pipeline {
    agent {
        label 'cpp-agent'
    }
    
    tools {
        // Reference the Ansible tool configured in Global Tool Configuration
        // Make sure you've added "Ansible" as a tool with "Install automatically" checked
        ansible 'ansible'
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
                        *.cpp \
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

        stage('Deploy with Ansible') {
            steps {
                // Option 1: Using the Ansible plugin's native step
                ansiblePlaybook(
                    playbook: './setup-server.yml',
                    inventory: './inventory',  // This should be a separate inventory file, NOT the playbook
                    credentialsId: 'ansible-ssh-key',
                    // Optional parameters:
                    // extraVars: [
                    //     key: 'value',
                    //     another_key: 'another_value'
                    // ],
                    // limit: 'localhost',
                    // tags: 'deploy'
                )
            }
        }
    }

    post {
        always {
            script {
                slackNotification(currentBuild.result)
            }
        }
    }
}

def slackNotification(String buildStatus = 'STARTED') {
    buildStatus = buildStatus ?: 'SUCCESS'
    def color = buildStatus == 'SUCCESS'  ? '#47ec05' :
                buildStatus == 'UNSTABLE' ? '#d5ee0d' :
                                            '#ec2805'
    
    def msg = "${buildStatus}: Job '${env.JOB_NAME}' #${env.BUILD_NUMBER}\n${env.BUILD_URL}"
    
    slackSend(color: color, message: msg)
}
